#include <iostream>
#include "my_string.h"

String f(String a, String b)
{
    a[2] = 'x';
    char c = b[3];
    std::cout << "in f: " << a << ' ' << b << ' ' << c << '\n';
    return b;
}

int main()
{
    /*String s("hello");
    String a(", world!");
    std::cout << s << std::endl;
    std::cout << a << std::endl;
    s += a;
    std::cout << s << std::endl;
    std::cout << a << std::endl;
    {
        String ss = s;
        ss += " And all, all, all!!!!";
        std::cout << ss << std::endl;
    }
    std::cout << s << std::endl;*/

    String x, y;
    std::cout << "Please enter two strings\n";
    std::cin >> x >> y;
    std::cout << "input: " << x << ' ' << y << '\n';

    String z = x;
    y = f(x, y);
    if (x != z) std::cout << "x corrupted!\n";

    x[0] = '!';
    if (x == z) std::cout << "write failed!\n";
    std::cout << "exit: " << x << ' ' << y << ' ' << z << '\n';
    
    return 0;
}
