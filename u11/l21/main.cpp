/*
 * Определите класс Index для хранения индекса функции возведения в степень
 * mypow(double, Index). Найдите возможность для 2**I отрабатывать в виде
 * вызова mypow(2, I)
 */

#include <cmath> // pow()
#include <cstdlib> // atoi()
#include <iostream> // streams

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

void usage()
{
    std::cout << "usage: program base power" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        usage();
    }
    else
    {
        int base = ::atoi(argv[1]);
        int power = ::atoi(argv[2]);

        std::cout << "base = " << base
                  << ", power = " << power << std::endl;

        Index i(power);
        std::cout << base << "**" << power << " = " << base ** i << std::endl;
    }
    return 0;
}
