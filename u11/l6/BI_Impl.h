#ifndef BI_IMPL_H
#define BI_IMPL_H

#include <vector>
#include <cmath>
#include "big_int.h"

// folowing two constants depends on each other
#define BIG_INT_IMPL_BASE 10000
#define BIG_INT_IMPL_DIGITS 4

class big_int::BI_Impl
{
public:
    // types
    typedef ::std::vector<int> ivector_t;
    typedef ivector_t::iterator ivector_iter_t;
    typedef ivector_t::const_iterator ivector_citer_t;

    // constructors
    BI_Impl(int value = 0); // done
    BI_Impl(const ivector_t &_digits, bool _is_positive = true); // done


    // ariphmetic
    void add(int value, int position); // done
    void sub(int value, int position); // done
    void mult(int value, int position);

    void cut_tail();
    void dbg_dump() const;

    int ref_cnt; // only big_int aware this member
    ivector_t digits;
    bool is_positive;

private:
    BI_Impl(const BI_Impl &); // do not use
    BI_Impl &operator=(const BI_Impl &); // do not use
};

// inline function

inline big_int::BI_Impl::BI_Impl(const ivector_t &_digits, bool _is_positive)
    : digits(_digits), is_positive(_is_positive) {}


#endif // BI_IMPL_H
