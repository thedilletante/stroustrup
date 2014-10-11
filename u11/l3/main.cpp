/* Определите класс INT, который ведет себя в точности как int.
 * Подсказка: определите INT::operator int().
 */

#include <iostream>

class INT
{
public:
    INT(int value = 0) : v(value) {}

    operator int() const
    {
        return v;
    }

private:
    int v;
};

int main()
{
    INT a = 5;
    INT b = 10;
    int c = 3, d = 6;

    c = a + d;
    b = d;
    return 0;
}
