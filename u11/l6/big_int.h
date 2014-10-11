#ifndef _BIG_INT
#define _BIG_INT

class big_int
{
public:
    big_int(long long value = 0);
    big_int(big_int &copy);
    big_int &operator=(big_int &copy);

    big_int(const char *rep);



    big_int &operator+=(const big_int &bi);
    big_int &operator-=(const big_int &bi);
    big_int &operator*=(const big_int &bi);
    big_int &operator/=(const big_int &bi);
    big_int &operator%=(const big_int &bi);

    friend bool operator==(const big_int &li, const big_int &ri);
    friend bool operator!=(const big_int &li, const big_int &ri);

private:
    struct IRep;
    IRep *rep;

};

struct big_ing::IRep
{
private:
    // deny copy
    IRep(const IRep &copy);
    IRep &operator=(const IRep &copy);

public:
    IRep(const std::vector<unsigned long long> &_digits);

    IRep *get_own_copy();

    bool positive;
    std::vector<unsigned long long> digits;
    size_t rf; // referense count
};

// inline functions


inline big_int::IRep::IRep(long long value)
    : positive(true), rf(1)
{
    if (value < 0)
    {
        positive = false;
        value = -value;
    }

    digits.push_back(value);
}

inline big_int::IRep *big_int::IRep::get_own_copy()
{
    if (rf == 1)
    {
        return this;
    }
    --rf;
    return new IRep(
}

#endif
