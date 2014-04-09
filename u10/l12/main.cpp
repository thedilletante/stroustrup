/*
Определите класс Char_queue так, чтобы открытый
интерфейс не зависил от представления. Реализуйте
Char_queue в виде (а) связного списка и (б) вектора.
Не беспокойтесь о многопоточности.
*/

#include <iostream>
#include "char_queue.h"

int main()
{
    Char_queue q;
    for (char ch = 'a'; ch <= 'z'; ++ch)
        q.enqueue(ch);

    while(q.size())
        std::cout << q.dequeue();

    return 0;

}