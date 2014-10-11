/*
Определите класс для анализирования, хранения,
вычисления и печати простых арифметических выражений,
состоящих из целых констант и операции +, -, * и /.
Открытый интерфейс должен выглядеть так:
class Expr
{
//...
public:
    Expr(const char *);
    int eval();
    void print();
};
Строковый аргумент конструктора Expr::Expr() является
выражением. Функция Expr::eval() возвращает значение
выражения, а Expr::print() выводит представление
выражения в cout. Программа может выглядеть примерно
так:
Expr x("123/4+123*4-3");
cout << "x=" << x.eval() << "\n";
x.print();
Определите класс Expr дважды: один раз для его
представления выберите список связных узлов, а другой
раз - строку. Поэкспериментируйте с разными способами
печаты выражения: с полной расстановкой скобок, в
постфиксной нотации и т.д.
*/

#include <iostream>
#include "expr.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        std::cout << "usage: " << argv[0] << " expr1 [... exprN]" << std::endl;
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            try
            {
                Expr a(argv[i]);
                a.print();
                std::cout << a.eval() << std::endl;
            }
            catch (Expr::SyntaxError e)
            {
                std::cout << "Syntax error on line " << i << " on pos " << e.position() << std::endl;
            }
        }
    }
    return 0;
}
