#define _DBG_MODE_
#include "my_string.h"


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
