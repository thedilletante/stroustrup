/*
 * Определите класс с арифметикой произвольной точности.
 * Протестируйте этот класс, вычислив факториал от 1000.
 * Подсказка: вам потребуется управление памятью вроде того,
 * что было сделано для класса String.
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <new>
//#include "big_int.h"

#ifdef _DBG_MODE_
#include <cstdio>
#define DBG(format, ...) \
    { \
        printf("DBG(%s,%s:%d): ", __FUNCTION__, __FILE__, __LINE__); \
        printf(format, ## __VA_ARGS__); \
        printf("\n"); \
    }
#else
#define DBG(format, ...)
#endif
/*int main()
{
    big_int a(437457723);
    for (int i = 0; i < 10000000; ++i)
        a += 437548665;
    std::cout << a << std::endl;
    return 0;
}*/

// - представление для чисел
// - определить операции сравнения для чисел

class big_int
{
public:
    // constructors & desctructor
    big_int(int value = 0);
    big_int(const big_int &);
    big_int &operator=(const big_int &);

    ~big_int();
    // comparators
    // ariphmetic
private:
    struct IRep;

    IRep *rep;
};


struct big_int::IRep
{
    bool is_positive;
    ::std::vector<int> digits;
    IRep(int value = 0);

    // constuctors and destructors do not care about ref_cnt
    int ref_cnt;


    IRep *get_own_copy()
    {
        IRep *ret_val = NULL;
        
        if (1 == this->ref_cnt)
        {
            ret_val = this;
        }
        else
        {
            try
            {
                ret_val = new IRep();
            }
            catch (::std::bad_alloc *ba)
            {
                assert(false && "how avoid bad_alloc in constructors???");
            }

            ret_val->is_positive = this->is_positive;
            ret_val->digits = this->digits;

            --this->ref_cnt;
            ret_val->ref_cnt = 1;
        }
        return ret_val;
    }
private:
    // non-copy
    IRep(const IRep &);
    IRep &operator=(const IRep &);

    static const int BASE = 1000;


    void set_sign(int value);
    void normalize_int(int value);
};

inline big_int::IRep::IRep(int value)
    : is_positive(true)
{
    DBG("test");
    set_sign(value);
    normalize_int(value);
}

inline void big_int::IRep::set_sign(int value)
{
    DBG("test");
    is_positive = (value >= 0);
}

inline void big_int::IRep::normalize_int(int value)
{
    DBG("test");
    for (int v = (value >= 0) ? value : -value; v != 0; v /= BASE)
    {
        digits.push_back(v % BASE);
    }
}


inline big_int::big_int(int value)
{
    DBG("test");
    try
    {
        rep = new IRep(value);
    }
    catch (::std::bad_alloc &ba)
    {
        // the question is how report about error in constructor
        assert(false && "not enough memory in constructor");
    }
    rep->ref_cnt = 1;
}

inline big_int::big_int(const big_int &copy)
{
    DBG("test");
    assert((NULL != copy.rep) && "copy object should be already created");
    rep = copy.rep;
    ++rep->ref_cnt;
}

inline big_int &big_int::operator=(const big_int &copy)
{
    DBG("test");
    assert((NULL != copy.rep) && "copy object should be already created");
    // how avoid of self-equls validation ???
    if (this != &copy)
    {
        // destroy own object
        assert((NULL != rep) && "we destroy more objects than created");
        if (0 == --rep->ref_cnt)
        {
           delete rep;
           rep = NULL;
        }
        rep = copy.rep;
        ++rep->ref_cnt;
        // copy from argument
    }
    return *this;
}

inline big_int::~big_int()
{
    DBG("test");
    assert((NULL != rep) && "we destroy more objects than create");    
    if (0 == --rep->ref_cnt)
    {
        delete rep;
        rep = NULL;
    }
}




void test_create_delete()
{
    big_int a(2345265436);
    big_int b(a);
    big_int c;
    c = b;
    DBG("test");
}


int main()
{
    test_create_delete();
}
