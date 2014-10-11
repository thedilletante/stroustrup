#ifndef _BIG_INT
#define _BIG_INT

#include <vector>

class BigInt
{
public:
    BigInt(int = 0);
    BigInt(const BigInt &);
    BigInt &operator=(const BigInt &);
    ~BigInt();
private:
    struct BIRep;
    BIRep *rep;
    class IRef;
};

struct BigInt::BIRep
{
    typedef std::vector<unsigned> ciphers_t;
    typedef ciphers_t::iterator cipher;
    
    ciphers_t ciphers;
    size_t ref_cnt;

    BIRep(const &ciphers) : ref_cnt(1) {}

    BIRep *get_own_copy()
    {
        if (ref_cnt == 1)
            return this;
        return new BIRep(ciphers);
    }
};

class BigInt::IRef
{
};

#endif // _BIG_INT
