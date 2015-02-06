#include "big_int.h"

#include <iomanip>
#include <algorithm>
#include "BI_Impl.h"
#include "helper.h"

/* not inline because 'BI_Impl' not declare */

big_int::big_int(int value)
{
    rep = new BI_Impl(value);
    rep->ref_cnt = 1;
    DBG("Created new big_int %p with value %d, ref_cnt %d", rep, value, rep->ref_cnt);
}

big_int::big_int(const big_int &l)
    : rep(l.rep)
{
    ++rep->ref_cnt;
    DBG("Copied big_int %p, ref_cnt %d", rep, rep->ref_cnt);
}

big_int &big_int::operator=(big_int l)
{
    DBG("Temporary argument with rep %p and ref_cnt %d", l.rep, l.rep->ref_cnt);
    this->swap(l);
    DBG("Swaped temporary %p, ref_cnt %d", l.rep, l.rep->ref_cnt);
    return *this;
}

big_int::~big_int()
{
    --rep->ref_cnt;
    DBG("Destroy big_int %p, ref_cnt %d", rep, rep->ref_cnt);
    if (0 == rep->ref_cnt)
    {
        DBG("Delete big_int %p", rep);
        delete rep;
        rep = NULL;
    }
}

void big_int::swap(big_int &l)
{
    using ::std::swap; // enable ADL
    DBG("Swap %p:%d <-> %p:%d", rep, rep->ref_cnt, l.rep, l.rep->ref_cnt);
    swap(this->rep, l.rep);
}

void swap(big_int &l, big_int &r)
{
    l.swap(r);
}

big_int &big_int::operator-()
{
    do_cow();
    rep->is_positive = !(rep->is_positive);
    return *this;
}
void big_int::do_cow()
{
    DBG("Change big_int %p ref_cnt %d", rep, rep->ref_cnt);
    if (1 != rep->ref_cnt)
    {
        --rep->ref_cnt;
        BI_Impl *old_rep = rep;
        rep = new BI_Impl(old_rep->digits, old_rep->is_positive);
        rep->ref_cnt = 1;
        DBG("Create new big_int %p with ref_cnt %d", rep, rep->ref_cnt);
    }
}
/* not inline because 'BI_Impl' not declare */

// comparators BEGIN
bool operator==(const big_int &l, const big_int &r)
{
    bool ret_val = false;

    big_int::BI_Impl &limpl = *l.rep;
    big_int::BI_Impl &rimpl = *r.rep;
    size_t l_size = 0;

    if ((limpl.is_positive == limpl.is_positive) &&
        ((l_size = limpl.digits.size()) == rimpl.digits.size()))
    {
        ret_val = true; // forward validation
        for (int i = 0; i < l_size; ++i)
        {
            if (limpl.digits[i] != rimpl.digits[i])
            {
                ret_val = false;
                break;
            }
        }
    }

    return ret_val;
}
bool operator>(const big_int &l, const big_int &r)
{
    bool ret_val = false;

    big_int::BI_Impl &limpl = *l.rep;
    big_int::BI_Impl &rimpl = *r.rep;

    if (limpl.is_positive == rimpl.is_positive)
    {
        int l_size = limpl.digits.size();
        int r_size = rimpl.digits.size();

        if (l_size == r_size)
        {
            for (int i = l_size - 1; i >= 0; --i)
            {
                if (limpl.digits[i] > rimpl.digits[i])
                {
                    ret_val = true;
                    break;
                }
            }
        }
        else
        {
            ret_val = (l_size > r_size);
        }

        if (!limpl.is_positive)
        {
            ret_val = !ret_val;
        }
    }
    else
    {
        ret_val = limpl.is_positive;
    }

    return ret_val;
}
// comparators END

// ariphmetic BEGIN
big_int &big_int::operator+=(const big_int &value)
{
    DBG("this %p with %d is_positive and %d digits", rep, rep->is_positive, rep->digits.size());
    DBG("other %p with %d is_positive and %d digits", value.rep, value.rep->is_positive, value.rep->digits.size());

    if (0 != value)
    {   // we defenetly will change this, so do copy-on-write
        do_cow();

        typedef void (big_int::BI_Impl::*modify_func_t)(int, int);
        modify_func_t modify_func = nullptr;
        big_int rv(value);
        int comp_dig = 0;

        // if signs of both numbers equal, just addition
        // else if all digits equal, we will get 0
        // else we should sub one number from other
        // if this is greater then value, sub value from this
        // else swap this and value

        if (rep->is_positive == value.rep->is_positive)
        {
            DBG("Signs are equals %d", rep->is_positive);
            modify_func = &big_int::BI_Impl::add;
        }
        else if (0 == (comp_dig = compare_digits(value))) // equals numbers
        {
            DBG("Equals digits");
            rep->digits.clear();
            rep->is_positive = true;
        }
        else if (1 == comp_dig) // this is greater
        {
            DBG("this is greater");
            modify_func = &big_int::BI_Impl::sub;
        }
        else
        {
            DBG("other greater");
            modify_func = &big_int::BI_Impl::sub;
            // revert
            swap(rv);
            do_cow();
            rep->is_positive = !rv.rep->is_positive;
        }

        if (nullptr != modify_func)
        {
            const BI_Impl::ivector_t &value_digits = rv.rep->digits;
            int position = 0;
            ::std::for_each(value_digits.begin(),
                            value_digits.end(),
                            [modify_func, this, &position](int digit)
                            {
                                (*rep.*modify_func)(digit, position);
                                ++position;
                            });
        }

        rep->dbg_dump();
        if (&big_int::BI_Impl::sub == modify_func)
        {
            rep->cut_tail();
        }
    }

    return *this;
}

big_int &big_int::operator-=(big_int value)
{
    return *this += (-value);
}

big_int &big_int::operator *=(const big_int &value)
{
    if (1 != value)
    {
        do_cow();
        if (0 == value)
        {
            rep->digits.clear();
            rep->is_positive = true;
        }
        else
        {
            const BI_Impl::ivector_t &value_digits = value.rep->digits;
            int position = 0;
            ::std::for_each(value_digits.begin(),
                            value_digits.end(),
                            [&position, this](int digit)
                            {
                                rep->mult(digit, position);
                            });
        }
    }
    return *this;
}

// ariphmetic END


// view BEGIN
::std::ostream &operator<<(::std::ostream &os, const big_int &l)
{
    if (false == l.rep->is_positive)
    {
        os << '-';
    }

    int i = l.rep->digits.size() - 1;
    if (i >= 0)
    {
        os << l.rep->digits[i];
        --i;
        while (i >= 0)
        {
            os << ::std::setw(BIG_INT_IMPL_DIGITS)
                << ::std::setfill('0');
            os << l.rep->digits[i];
            --i;
        }
        os << ::std::setw(0) << ::std::setfill(' ');
    }
    else
    {
        os << '0';
    }
    return os;
}

// view BEGIN


int big_int::compare_digits(const big_int &val) const
{
    int ret_val = 0;

    size_t l_size = rep->digits.size();
    size_t r_size = val.rep->digits.size();

    if (l_size == r_size)
    {
        for (int i = l_size - 1; i > 0; --i)
        {
            if (rep->digits[i] != val.rep->digits[i])
            {
                ret_val = (rep->digits[i] > val.rep->digits[i]) ? 1 : -1;
                break;
            }
        }
    }
    else
    {
        ret_val = (l_size > r_size) ? 1 : -1;
    }

    return ret_val;
}
