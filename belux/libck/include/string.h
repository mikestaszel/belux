#ifndef _STRING_H_LIBCK
#define _STRING_H_LIBCK

#include <sys/cdefs.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char*);
int memcmp(const void* str1, const void* str2, size_t count);
void* memmove(void* dest, void* src, size_t len);
void* memcpy(void* dest, const void* src, size_t len);
void* memset(void* dest, int val, size_t len);

#ifdef __cplusplus
}
#endif

#endif
