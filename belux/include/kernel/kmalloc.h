#ifndef _KERNEL_KMALLOC_H
#define _KERNEL_KMALLOC_H

typedef struct chunk_header chunk_header_t;

struct chunk_header {
	chunk_header_t* next;
	chunk_header_t* prev;
	size_t size;
	unsigned short used;
};

void* kmalloc(size_t size);
void* krealloc(void* ptr, size_t new_size);
void kfree(void* ptr);

#endif
