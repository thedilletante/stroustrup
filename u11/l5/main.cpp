/* Определите класс RINT, который ведет себя как LINT, но для
 * представления чисел использует по крайней мере 64 бита.
 */

#include <iostream>

class RINT
{
public:
    RINT(int value = 0); 

    int getValue() const;
    
    RINT &operator+=(const RINT &v);
    RINT &operator-=(const RINT &v);
    RINT &operator*=(const RINT &v);
    RINT &operator/=(const RINT &v);

    friend ::std::ostream &operator<<(::std::ostream &out, const RINT &v);

private:

    static const int BITS_IN_BYTE = 8;
    static const int BYTES_FOR_DIGIT_REP = 8;
    char rep[BYTES_FOR_DIGIT_REP];
    bool is_positive;


    char get_nth_byte(int value, int n) const;
};

inline char RINT::get_nth_byte(int value, int n) const
{
    return (char)(value >> (BITS_IN_BYTE * (n - 1)) & 0xff);
}

RINT::RINT(int value)
{
    is_positive = (value < 0);
    if (!is_positive)
    {
        value = -value;
    }
    for (int i = 0; i < BYTES_FOR_DIGIT_REP; ++i)
    {
        rep[i] = get_nth_byte(value, i + 1);
    }
}

RINT &RINT::operator+=(const RINT &v)
{
    return *this;
}

RINT &RINT::operator-=(const RINT &v)
{
    return *this;
}

RINT &RINT::operator*=(const RINT &v)
{
    return *this;
}

RINT &RINT::operator/=(const RINT &v)
{
    return *this;
}

inline RINT operator+(const RINT &l, const RINT &r)
{
    RINT ret = l;
    return ret += r;
}

inline RINT operator+(const RINT &l)
{
    return l;
}

inline RINT operator-(const RINT &l, const RINT &r)
{
    RINT ret = l;
    return ret -= r;
}


inline RINT operator-(const RINT &l)
{
    return 0 - l;
}

inline RINT operator*(const RINT &l, const RINT &r)
{
    RINT ret = l;
    return ret *= r;
}

inline RINT operator/(const RINT &l, const RINT &r)
{
    RINT ret = l;
    return ret /= r;
}

inline std::ostream &operator<<(std::ostream &out, const RINT& v)
{
    if (!v.is_positive)
    {
        out << '-';
    }
    for (
    return out;
}

int main()
{
    RINT l = 10;
    std::cout << l << std::endl;
    return 0;
}
