#ifndef ILOGGER
#define ILOGGER

#define DEBUG

#include <cstdio>
#include <stdarg.h>

#define PRINT_PREFIX "SM:Default: "

#define PRINT_INF(DESC, ...) PRINT_EX("[INF]: " PRINT_PREFIX DESC "\n", ##__VA_ARGS__)
#define PRINT_ERR(DESC, ...) PRINT_EX("[ERR]: " PRINT_PREFIX DESC "\n", ##__VA_ARGS__)
#define PRINT_WRN(DESC, ...) PRINT_EX("[WRN]: " PRINT_PREFIX DESC "\n", ##__VA_ARGS__)

inline void PRINT_EX(const char a_acArg[] ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, a_acArg);
    vprintf(a_acArg, args);
    va_end(args);
#endif
    return;
}

#endif // ILOGGER



