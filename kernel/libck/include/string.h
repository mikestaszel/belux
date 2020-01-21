#ifndef _STRING_H_LIBCK
#define _STRING_H_LIBCK

#include <sys/cdefs.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char*);
void* memset(void*, int, size_t);

#ifdef __cplusplus
}
#endif

#endif
