#ifndef _CHAR_QUEUE
#define _CHAR_QUEUE

#include <cstdio>
#include <stdexcept>
#ifdef CHAR_QUEUE_LIST_IMPL
#include <list>
#else
#include <vector>
#endif

class Char_queue
{
public:

    bool enqueue(char ch);
    char dequeue();

    size_t size() { return container.size(); }

private:
#ifdef CHAR_QUEUE_LIST_IMPL
    std::list<char>
#else
    std::vector<char>
#endif
    container;
};


#endif // _CHAR_QUEUE