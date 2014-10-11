#ifndef _MY_STRING
#define _MY_STRING

#include <stdio.h>

#ifdef _DBG_MODE_
#define DBG(format, ...) \
    { \
        printf("DBG(%s,%s:%d): ", __FUNCTION__, __FILE__, __LINE__); \
        printf(format, ## __VA_ARGS__); \
        printf("\n"); \
    }
#else
#define DBG(format, ...)
#endif

#include <assert.h>
#include <string.h>

#include <iostream>

#define EMPTY_STRING ""

class String
{
private:
    class Cref; // I will try to use const and non-const operator[]
                // Impossible. non-const oparator[] called always.
public:
    class Range {};

    String();
    String(const char *);
    String(const String &);
    String &operator=(const char *);
    String &operator=(const String &);
    ~String();

    char read(int) const;
    void write(int, char);

    char operator[](int) const;
    Cref operator[](int);

    int size() const;

    String &operator+=(const String &);
    String &operator+=(const char *);

    friend ::std::ostream &operator<<(::std::ostream &, const String &);
    friend ::std::istream &operator>>(::std::istream &, String &);

    friend bool operator==(const String &, const char *);
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const char *);
    friend bool operator!=(const String &, const String &);

private:
    struct Srep;
    Srep *rep;

    void check(int i) const;
    void clear_rep();
    void cat(const char *s, int n);
};

// non-member useful functions

String operator+(const String &, const String &);
String operator+(const String &, const char*);


struct String::Srep
{
private:
    Srep(const Srep &); // deny copy
    Srep &operator=(const Srep &); // deny copy
public:
    char *s;    // pointer to elements
    int sz;     // size of characters
    int n;      // reference counter

    Srep(int, const char *);
    ~Srep();

    Srep *get_own_copy(); // if necessary clone
    void assign(int, const char *);
};

class String::Cref
{
public:
    operator char() const
    {
        DBG("reading %d pos <%p>", i, &s);
        return s.read(i);
    }
    char operator=(char c)
    {
        s.write(i, c);
        DBG("writing %d pos to '%c' <%p>", i, c, &s);
        return c;
    }

private:
    friend class String;
    String &s;
    int i;

    Cref(String &ss, int ii) : s(ss), i(ii)
    { DBG("string<%p> position = %d", &s, i); }
    Cref(const Cref& r) : s(r.s), i(r.i)
    { DBG("copy string<%p> position = %d", &s, i); }
    Cref(); // unusage  - do not define
};

// inline functions
// if it will grow - move to .cpp file


/************************************************************/
/*************Srep related functions*************************/
/************************************************************/

inline String::Srep::Srep(int nsz, const char *p)
    : n(1), sz(nsz), s(new char[nsz + 1])
{
    ::strncpy(s, p, sz);
    DBG("construct Srep with %d characters <%p>", sz, this);
}

inline String::Srep::~Srep()
{
    DBG("destruct Srep(ref_cnt=%d) with %d charactes <%p>", n, sz, this);
    delete[] s;
}

inline String::Srep *String::Srep::get_own_copy()
{
    DBG("n = %d", n);
    if (n == 1)
    {
        return this;
    }
    n--;
    return new Srep(sz, s);
}

inline void String::Srep::assign(int nsz, const char *p)
{
    DBG("replace all %d-string with %d characters <%p>", sz, nsz, this);
    if (sz != nsz)
    {
        delete[] s;
        sz = nsz;
        s = new char[sz + 1];
    }
    ::strncpy(s, p, sz);
}

/************************************************************/
/*************String related functions***********************/
/************************************************************/

inline String::String()
    : rep(new Srep(0, EMPTY_STRING))
{
    DBG("new empty string");
}

inline String::String(const String &x)
    : rep(x.rep)
{
    rep->n++;
    DBG("copy constuctor, get copy rep, rf %d", rep->n);
}

inline String::~String()
{
    clear_rep();
    DBG("delete string %p", this);
}

inline String &String::operator=(const String &x)
{
    DBG("copy<%p> of another string<%p>", this, &x);
    if (this != &x)
    {
        clear_rep();
        rep = x.rep;
    }
    return *this;
}

inline String::String(const char *s)
    : rep(new Srep(::strlen(s), s))
{
    DBG("constuct string with char <%p>", this);
}

inline String &String::operator=(const char *s)
{
    if (rep->n == 1)
    {
        DBG("copy<%p> from char, use old Srep<%p>", this, rep);
        rep->assign(::strlen(s), s); // use old Srep, nobody use it
    }
    else
    {
        int rf_cnt = --rep->n;
        rep = new Srep(::strlen(s), s); // use new Srep
        DBG("copy<%p> from char, use new Srep<%p> old rf_cnt = %d", this, rep, rf_cnt);
    }
    return *this;
}




inline int String::size() const
{
    return rep->sz;
}

inline void String::check(int i) const
{
    if ((i < 0) || (i > size()))
    {
        DBG("someone want to %d index in %d-string", i, size());
        throw Range();
    }
}

inline void String::clear_rep()
{
    DBG("rf_cnt = %d", rep->n);
    if (--rep->n == 0)
    {
        delete rep;
        rep = NULL;
    }
}


inline char String::read(int i) const
{
    DBG("unsafe reading %d index in %d-string", i, size());
    return rep->s[i];
}

inline void String::write(int i, char c)
{
    DBG("unsafe writing %d index in %d-string", i, size());
    rep = rep->get_own_copy();
    DBG("own_copy return <%p> rep", rep);
    rep->s[i] = c;
}

inline char String::operator[](int i) const
{
    check(i);
    DBG("reading %d character '%c'", i, rep->s[i]);
    return rep->s[i];
}

inline String::Cref String::operator[](int i)
{
    check(i);
    DBG("build new Cref<%p> on position %d", this, i);
    return Cref(*this, i);
}


inline void String::cat(const char *s, int n)
{
    if (n > 0)
    {
        Srep *tmp = new Srep(n + size(), rep->s);
        ::strncat(tmp->s, s, n);
        clear_rep();
        rep = tmp;
    }
}

inline bool operator==(const String &x, const char *s)
{
    return strncmp(x.rep->s, s, x.size()) == 0;
}
inline bool operator==(const String &x, const String &y)
{
    return strncmp(x.rep->s, y.rep->s, x.size()) == 0;
}
inline bool operator!=(const String &x, const char *s)
{
    return !(x == s);
}
inline bool operator!=(const String &x, const String &y)
{
    return !(x == y);
}

inline String &String::operator+=(const String &x)
{
    cat(x.rep->s, x.size());
    return *this;
}

inline String &String::operator+=(const char *s)
{
    cat(s, ::strlen(s));
    return *this;
}

inline ::std::ostream &operator<<(::std::ostream &os, const String &s)
{
    return os << s.rep->s;
}




inline String operator+(const String &x, const String &y)
{
    String res = x;
    return res += y;
}

inline String operator+(const String &x, const char *s)
{
    String res = x;
    return res += s;
}

#endif
