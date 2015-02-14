#include "BI_Impl.h"
#include "helper.h"
#include <assert.h>

big_int::BI_Impl::BI_Impl(int value)
{
    is_positive = (value >= 0);
    value = ::std::abs(value);
    int tmp_value = 0;
    DBG("build vector: is_positive %d, abs value %d", is_positive, value);
    while (value > 0)
    {
        tmp_value = value % BIG_INT_IMPL_BASE;
        value /= BIG_INT_IMPL_BASE;
        DBG("tmp_value %d, rest %d", tmp_value, value);
        digits.push_back(tmp_value);
    }
}

void big_int::BI_Impl::add(int value, int position)
{
    assert((position >= 0) && "position should be greater or equal 0");
    assert((value >= 0) && "value should be greater or equal 0");

    DBG("Increase value with %d from position %d", value, position);

    if (position > digits.size())
    {
        DBG("We need to insert too forward, resize to %d", position);
        digits.resize(position, 0);
    }

    int sub_value = 0;
    int tmp_value = 0;
    while (value > 0)
    {
        if (position == digits.size())
        {
            digits.push_back(0);
        }
        sub_value = value % BIG_INT_IMPL_BASE;
        value /= BIG_INT_IMPL_BASE;
        DBG("sub_value %d, rest_value %d", sub_value, value);

        tmp_value = sub_value + digits[position];
        DBG("tmp_value %d", tmp_value);
        value += tmp_value / BIG_INT_IMPL_BASE;
        tmp_value %= BIG_INT_IMPL_BASE;
        DBG("digit on %d position is %d, rest is %d", position, tmp_value, value);

        digits[position] = tmp_value;
        ++position;
    }
}

void big_int::BI_Impl::sub(int value, int position)
{
    assert((position >= 0) && "position should be greater or equal 0");
    assert((value >= 0) && "value should be greater or equal 0");
    assert((value < BIG_INT_IMPL_BASE) && "value should be smaller then BASE");

    // we already know, that we are greater then value
    size_t size = digits.size();
    assert((position < size) && ("position must be smaller then size in sub"));

    DBG("Sub %d value from %d position", value, position);
    if (value > digits[position])
    {
        digits[position] += BIG_INT_IMPL_BASE;
        // sub from next
        for (int i = position + 1; ; ++i)
        {
            DBG("Get loan from %d position with %d digit", i, digits[i]);
            if (digits[i] > 0)
            {
                --digits[i];
                break;
            }
            else
            {
                digits[i] = BIG_INT_IMPL_BASE - 1;
            }
        }
    }

    digits[position] -= value;
    DBG("End of sub and val %d", digits[position]);
}

void big_int::BI_Impl::dbg_dump() const
{
    DBG("dump start");
    DBG("is_positive: %d", is_positive);
    for (size_t i = 0, size = digits.size(); i < size; ++i)
    {
        DBG("%d position: %d", i, digits[i]);
    }
    DBG("dump finish");
}

void big_int::BI_Impl::cut_tail()
{
    int i = digits.size();
    for (; i > 0; --i)
    {
        if (digits[i - 1] != 0)
        {
            DBG("First not 0 is %d on %d pos", digits[i - 1], i - 1);
            break;
        }
    }

    if (i != digits.size())
    {
        if (i == 0)
        {
            DBG("No elements at all, clear");
            digits.clear();
        }
        else
        {
            DBG("Resize to %d size", i);
            digits.resize(i);
        }
    }
}
