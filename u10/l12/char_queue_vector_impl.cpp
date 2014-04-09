#define CHAR_QUEUE_VECTOR_IMPL
#include "char_queue.h"

bool Char_queue::enqueue(char ch)
{
    container.push_back(ch);
    return true;
}

char Char_queue::dequeue()
{
    if (size() == 0)
        throw std::out_of_range("container is empty");
    char ch = container.front();
    container.erase(container.begin());
    return ch;
}