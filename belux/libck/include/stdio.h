#ifndef _STDIO_H_LIBCK
#define _STDIO_H_LIBCK

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void printf(char* fmt, ...);
int putchar(int);

#ifdef __cplusplus
}
#endif

#endif
