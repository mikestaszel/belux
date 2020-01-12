#ifndef _STDIO_H_LIBCK
#define _STDIO_H_LIBCK 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char*);
int putchar(int);

#ifdef __cplusplus
}
#endif

#endif
