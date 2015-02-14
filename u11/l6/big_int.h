#ifndef _BIG_INT
#define _BIG_INT

#include <iostream> // for ::std::ostream

class big_int
{
public:
    // constructors & desctructor
    big_int(int value = 0); // done
    big_int(const big_int &); // done
    big_int &operator=(big_int); // done
    ~big_int(); // done

    void swap(big_int &); // done

    // comparators
    friend bool operator==(const big_int &, const big_int &); // done
    friend bool operator>(const big_int &, const big_int &); // done

    // ariphmetic
    //friend big_int operator*(big_int, const big_int &); // done
    //friend big_int operator/(big_int, const big_int &); // done
    //friend big_int operator%(big_int, const big_int &); // done

    big_int &operator+=(const big_int &); // done
    big_int &operator-=(const big_int &); // done
    big_int &operator/=(const big_int &); // TODO
    big_int &operator%=(const big_int &); // TODO

    big_int operator*(const big_int &) const;

    big_int operator-() const; // done

    // view
    friend ::std::ostream &operator<<(::std::ostream &, const big_int &); // done
private:
    class BI_Impl;

    BI_Impl *rep;

    void do_cow(); // copy-on-write mechanism // done
    int compare_digits(const big_int &val) const; // -1 = val greater, 1 = this greater, 0 = equals // done
};

void swap(big_int &, big_int &); // done

big_int &operator++(big_int &); // done
big_int operator++(big_int &, int); // done
big_int &operator--(big_int &); // done
big_int operator--(big_int &, int); // done

big_int operator+(const big_int &); // done

// inline ligth-weigth functions

inline bool operator!=(const big_int &l, const big_int &r)
{
    return !(l == r);
}
inline bool operator<(const big_int &l, const big_int &r)
{
    return (l != r) && !(l > r);
}
inline bool operator>=(const big_int &l, const big_int &r)
{
    return ((l > r) || (l == r));\
}
inline bool operator<=(const big_int &l, const big_int &r)
{
   return ((l < r) || (l == r));
}

inline big_int operator+(big_int l, const big_int &r) { return l += r; }
inline big_int operator-(big_int l, const big_int &r) { return l -= r; }
inline big_int operator/(big_int l, const big_int &r) { return l += r; }
inline big_int operator%(big_int l, const big_int &r) { return l += r; }

inline big_int &operator++(big_int &l) { return l += 1; }
inline big_int operator++(big_int &l, int) { big_int res(l); l += 1; return res; }
inline big_int &operator--(big_int &l) { return l -= 1; }
inline big_int operator--(big_int &l, int) { big_int res(l); l -= 1; return res; }

inline big_int operator+(big_int &l) { return l; /* for operator- symmetry */ }

inline big_int &operator*=(big_int &l, const big_int &r)
{
    l = l * r;
    return l;
}


#endif
