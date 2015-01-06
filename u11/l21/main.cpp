/*
 * Определите класс Index для хранения индекса функции возведения в степень
 * mypow(double, Index). Найдите возможность для 2**I отрабатывать в виде
 * вызова mypow(2, I)
 */

#include <cmath>
#include <iostream>

class Iptr
{
public:
    friend class Index;
private:

    Iptr(int _ind = 0) : ind(_ind) {}
    int ind;

    friend double operator*(double d, const Iptr &i)
    {
        return ::pow(d, i.ind);
    }
};

class Index
{
public:
    Index(int _ind = 0) : ind(_ind) {}

    Iptr operator*()
    {
        return Iptr(ind);
    }

private:
    int ind;
};

int main()
{
    std::cout << ::pow(2, 3) << std::endl;
    Index i(5);
    std::cout << 2**i << std::endl;
    std::cout << 5**i << std::endl;
    return 0;
}
