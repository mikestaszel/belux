#ifndef _STDIO_H_LIBCK
#define _STDIO_H_LIBCK

#include <sys/cdefs.h>
#include <stdint.h>
#include <string.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

void printf(char* fmt, ...);
int putchar(int);

#ifdef __cplusplus
}
#endif

#define off_t int64_t
#define SEEK_CUR 1

typedef struct _IO_FILE FILE;

struct _IO_FILE {
    unsigned flags;
    char *rpos, *rend;
    char *wend, *wpos, *wbase;

    size_t (*read)(FILE *, char *, size_t);

    size_t (*write)(FILE *, const char *, size_t);

    off_t (*seek)(FILE *, off_t, int);

    int (*close)(FILE *);

    char *buf;
    size_t buf_size;
    FILE *prev, *next;
    int fd;
    signed char mode; // 'r' or 'w' I guess
    signed char lbf; // Line buffer (format?)
    int lock;
    void *cookie;
    off_t off;
};

// TODO flesh out
struct stat {
    off_t st_size;
};

extern FILE *stdout;

#endif
