#define CHAR_QUEUE_LIST_IMPL
#include "char_queue.h"

bool Char_queue::enqueue(char ch)
{
    container.push_front(ch);
    return true;
}

char Char_queue::dequeue()
{
    if (size() == 0)
        throw std::out_of_range("container is empty");
    char ch = container.back();
    container.pop_back();
    return ch;
}