#ifndef HELPER_H
#define HELPER_H

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

#endif // HELPER_H
