#ifndef _KERNEL_KMALLOC_H
#define _KERNEL_KMALLOC_H

#define bool _Bool
#define true 1
#define false 0

#include <string.h>
#include <stdint.h>

void* kmalloc(size_t size);
void* krealloc(void* ptr, size_t new_size);
void kfree(void* ptr);
void print_chunk_debug(void* ptr, bool recursive);

#endif
