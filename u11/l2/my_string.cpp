#define _DBG_MODE_
#include "my_string.h"


String &String::operator+=(const String &x)
{
    cat(x.rep->s, x.size());
    return *this;
}

String &String::operator+=(const char *s)
{
    int n = ::strlen(s);
    cat(s, n);
    return *this;
}

::std::ostream &operator<<(::std::ostream &os, const String &s)
{
    return os << s.rep->s;
}

::std::istream &operator>>(::std::istream &is, String &s)
{
    char ch;

    // skip spaces
    while (is.get(ch) && ::isspace(ch));

    if (ch)
    {
        int len = 0;
        char buf[254] = {0};
        do
        {
            buf[len++] = ch;
        }
        while (is.get(ch) && !::isspace(ch));
        DBG("readed %d characters", len);
        s.rep->assign(len, buf);
    }
    return is;
}
