#ifndef _BIG_INT
#define _BIG_INT

#include <stdio.h>

#ifdef _DBG_MODE_
#define DBG(format, ...) \
    { \
        printf("DBG(%s,%s:%d): ", __FUNCTION__, __FILE__, __LINE__); \
        printf(format, ## __VA_ARGS__); \
        printf("\n"); \
    }
#else
#define DBG(format, ...)
#endif

#include <assert.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <iomanip>

class big_int
{
public:
    big_int(int value = 0);
    big_int(const big_int &copy);
    big_int &operator=(const big_int &copy);
    ~big_int();

    //big_int(const char *rep);

    //big_int &operator+=(const big_int &bi);
    //big_int &operator-=(const big_int &bi);
    //big_int &operator*=(const big_int &bi);
    //big_int &operator/=(const big_int &bi);
    //big_int &operator%=(const big_int &bi);
    big_int &operator+=(int value);

    friend bool operator==(const big_int &li, const big_int &ri);
    friend bool operator!=(const big_int &li, const big_int &ri);
    friend bool operator>(const big_int &li, const big_int &ri);
    friend bool operator<(const big_int &li, const big_int &ri);
    
    friend std::ostream &operator<<(std::ostream &os, const big_int &i);

private:
    struct IRep;
    IRep *rep;
};

// non-member usefull functions

// big_int operator+(const big_int &a, const big_int &b);
// big_int operator-(const big_int &a, const big_int &b);
// big_int operator*(const big_int &a, const big_int &b);
// big_int operator/(const big_int &a, const big_int &b);
// big_int operator%(const big_int &a, const big_int &b);

#define DEFAULT_GROWING 20

struct big_int::IRep
{
    static const int BASE = 1000000;

    int ref_cnt;

    int capasity;
    int last_rank;

    bool is_positive;
    int *digits;

    IRep(int value = 0);
    IRep(int *d, int c, int l, bool p)
        : capasity(c), ref_cnt(1), last_rank(l), is_positive(p),
          digits(new int[capasity])
    {
        DBG("constructing IRep from another array (%d, %d)", capasity, last_rank);
        ::memcpy(digits, d, last_rank * sizeof(int));
    }
    ~IRep();

    void grow_by(int elements);
    
    IRep *get_own_copy();

    void add_int_from_rank(int value, size_t rank = 0);

private:
    IRep(const IRep &copy); // not implemented cause not used
    IRep &operator=(const IRep &copy); // the same reason
};

inline big_int::IRep::IRep(int value)
    : ref_cnt(1), is_positive(true),
      capasity(DEFAULT_GROWING), last_rank(0),
      digits(new int[capasity])
{
    if (value < 0)
    {
        is_positive = false;
        add_int_from_rank(-value);
    }
    else
    {
        add_int_from_rank(value);
    }
}

inline big_int::IRep::~IRep()
{
    assert(digits != NULL);
    delete[] digits;
}

inline void big_int::IRep::add_int_from_rank(int value, size_t rank)
{
    while (value)
    {
        if (rank >= capasity)
        {
            grow_by((rank - capasity < DEFAULT_GROWING)
                        ? DEFAULT_GROWING
                        : rank - capasity + DEFAULT_GROWING);
        }
        DBG("assigning %d to %ld", value % BASE, rank);
        digits[rank] += value % BASE;
        value /= BASE;

        if (digits[rank] >= BASE)
        {
            value += digits[rank] / BASE;
            digits[rank] %= BASE;
        }

        ++rank;
    }
    if (rank > last_rank)
    {
        last_rank = rank;
    }
}

inline void big_int::IRep::grow_by(int elements)
{
    int *new_digits = new int[capasity + elements];
    ::memcpy(new_digits, digits, capasity * sizeof(int));
    delete[] digits;
    digits = new_digits;
    capasity += elements;
    DBG("new size of IRep %d", capasity);
}

inline big_int::IRep *big_int::IRep::get_own_copy()
{
    if (1 == ref_cnt)
    {
        return this;
    }
    --ref_cnt;
    DBG("new copy");
    return new IRep(digits, capasity, last_rank, is_positive);
}



inline big_int::big_int(int value)
    : rep(new IRep(value))
{
    DBG("new value %d", value);
}

inline big_int::big_int(const big_int &copy)
    : rep(copy.rep)
{
    ++rep->ref_cnt;
    DBG("copy %d", rep->ref_cnt);
}

inline big_int &big_int::operator=(const big_int &copy)
{
    if (this != &copy)
    {
        if ((rep != copy.rep) &&
            (NULL != rep) &&
            (rep->ref_cnt == 1))
        {
            delete rep;
            rep = copy.rep;
            ++rep->ref_cnt;
            DBG("copy %d", rep->ref_cnt);
        }
    }
    return *this;
}

inline big_int::~big_int()
{
    DBG("deleting %d", rep ? rep->ref_cnt : 0);
    if ((NULL != rep) && (rep->ref_cnt-- == 1))
    {
        delete rep;
        rep = NULL;
    }
}

inline big_int &big_int::operator+=(int value)
{
    if (rep->ref_cnt > 1)
    {
        --rep->ref_cnt;
        rep = rep->get_own_copy();
    }
    rep->add_int_from_rank(value);
    return *this;
}

inline ::std::ostream &operator<<(::std::ostream &os, const big_int &i)
{
    if (i.rep->last_rank)
    {
        os << i.rep->digits[i.rep->last_rank - 1];
    }
    for (int rank = i.rep->last_rank - 1; rank > 0; --rank)
    {
        os << std::setfill('0') << std::right << std::setw(6) << i.rep->digits[rank - 1];
    }
    return os;
}
#endif
