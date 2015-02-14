/*
 * Определите класс с арифметикой произвольной точности.
 * Протестируйте этот класс, вычислив факториал от 1000.
 * Подсказка: вам потребуется управление памятью вроде того,
 * что было сделано для класса String.
 */

#include <iostream>
#include "helper.h"
#include "big_int.h"


void test_create_delete()
{
    DBG("%s start", __FUNCTION__);
    big_int a(-23450265);
    big_int b(a);
    big_int c;
    c = b;
    {
        big_int d = c;
    }
    std::cout << c << std::endl;
    std::cout << 'a' << std::endl;
    DBG("%s end", __FUNCTION__);
}


void test_compare(const big_int &a, const big_int &b)
{
    DBG("%s start", __FUNCTION__);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a == b = " << (a == b) << std::endl;
    std::cout << "a != b = " << (a != b) << std::endl;
    std::cout << "a > b = " << (a > b) << std::endl;
    std::cout << "a < b = " << (a < b) << std::endl;
    std::cout << "a >= b = " << (a >= b) << std::endl;
    std::cout << "a <= b = " << (a <= b) << std::endl;
    DBG("%s end", __FUNCTION__);
}


void test_add()
{
    big_int a(3534545);
    a += 99669234;
    std::cout << a << std::endl;
    a -= 2342355;
    std::cout << a << std::endl;
    a += (-43566);
    std::cout << a << std::endl;

    big_int b(234);
    b -= (24564767);
    std::cout << b << std::endl;
    std::cout << "a + b" << a + b << std::endl;
}

void test_add_and_sub(const big_int &a, const big_int &b)
{
    DBG("%s start", __FUNCTION__);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "b + a = " << b + a << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "b - a = " << b - a << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    DBG("%s end", __FUNCTION__);
}

void test_mult(const big_int &a, const big_int &b)
{
    DBG("%s start", __FUNCTION__);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "b * a = " << b * a << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    DBG("%s end", __FUNCTION__);
}

big_int factorial(const big_int &a)
{
    big_int ret_val = 1;
    for (big_int i = 2; i <= a; ++i)
    {
        ret_val *= i;
    }
    return ret_val;
}

int main(int argc, char *argv[])
{
//    test_create_delete();
//    test_compare(234123,22345);
//    test_compare(234123,-22345);
//    test_compare(-234123,22345);
//    test_compare(2340123,220034);
//    test_compare(2340123,-220034);
//    test_compare(2340123,2340123);

    //test_add();


//    test_add_and_sub(26983576, 23595);
//    test_add_and_sub(764576, 100000000);
//    test_add_and_sub(56797993, 56797993);
//    test_add_and_sub(34654, -389739);


    //test_mult(2,2);
    /*
    test_mult(-3,432);
    test_mult(1,34);
    test_mult(2342,-1);
    test_mult(0,34);*/

    if (argc < 2)
    {
        std::cout << "usage: big_int value" << std::endl;
    }
    else
    {
        big_int a = ::atoi(argv[1]);
        std::cout << "factorial(" << a << ") = " << factorial(a) << std::endl;
    }
}
