/* Определите класс RINT, который ведет себя как int,
 * за исключением того, что допустимыми являются лишь
 * +, - (унарные и бинарные), *, /, %.
 * Подсказка: не определяйте RINT::operator int().
 */


#include <iostream>

class RINT
{
public:
    RINT(int value = 0) : v(value) {}

    int getValue() const { return v; }

private:
    int v;
};

inline int operator+(const RINT &l, const RINT &r)
{
    return l.getValue() + r.getValue();
}

inline int operator+(const RINT &l)
{
    return +(l.getValue());
}

inline int operator-(const RINT &l)
{
    return -(l.getValue());
}

inline int operator-(const RINT &l, const RINT &r)
{
    return l.getValue() - r.getValue();
}

inline int operator*(const RINT &l, const RINT &r)
{
    return l.getValue() * r.getValue();
}

inline int operator/(const RINT &l, const RINT &r)
{
    return l.getValue() / r.getValue();
}


int main()
{
    RINT l = 10;
    std::cout << -l << std::endl;
    return 0;
}
