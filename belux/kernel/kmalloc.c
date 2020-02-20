#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <kernel/kmalloc.h>
#include <kernel/tty.h>
#include <kernel/mmu.h>
#include <kernel/serial.h>

#define PAGE_SIZE 0x400000
uintptr_t mmap_end = 0;
void* start_chunk;

// Initialized from multiboot:
void* malloc_memory_start = NULL;
void* malloc_memory_end = NULL;
static bool initial_alloc = true;

typedef struct chunk_header chunk_header_t;

struct chunk_header {
	chunk_header_t* next;
	chunk_header_t* prev;
	size_t size;
	unsigned short used;
};

static int try_reclaim(chunk_header_t* start, size_t size) {
	chunk_header_t* current_chunk = start;
	if (current_chunk->next == NULL) {
		return false;
	}

	size_t unused = current_chunk->size;
	current_chunk = current_chunk->next;
	while (!current_chunk->used) {
		chunk_header_t *next_chunk = current_chunk->next;
		if (next_chunk == NULL) {
			return 2; // Hit end of chunks
		}

		unused += (uintptr_t) next_chunk - (uintptr_t) current_chunk;
		if (unused >= ALIGN(size, 4) + sizeof(chunk_header_t)) {
			next_chunk->prev = start;
			start->next = next_chunk;
			return 1;
		}
		current_chunk = next_chunk;
	}
	return 0;
}

static bool ensure_pages(void* new_end) {
	uintptr_t phys_end = (uintptr_t) virt_to_phys(new_end);
	while (mmap_end < phys_end) {
		uintptr_t next_page = mmap_end;
		if (next_page == 0) {
			next_page = ALIGN((uintptr_t) malloc_memory_start, PAGE_SIZE);
		}
		if (next_page + PAGE_SIZE > (uintptr_t) malloc_memory_end) {
			// Oops, out of memory
			return false;
		}
		page_table_set(next_page, (uintptr_t) phys_to_virt((void*) next_page), 0x83);
		mmap_end = next_page + PAGE_SIZE;
	}
	return true;
}

static chunk_header_t* find_unused_chunk(const size_t chunk_size) {
	if (initial_alloc) {
		if (malloc_memory_start == NULL) {
			return NULL;
		}

		start_chunk = phys_to_virt((void *) ALIGN((uintptr_t) malloc_memory_start, PAGE_SIZE));
		ensure_pages(start_chunk + sizeof(chunk_header_t) + chunk_size);

		initial_alloc = false;

		chunk_header_t* header = start_chunk;
		memset(header, 0, sizeof(chunk_header_t));
		return header;
	}

	chunk_header_t *header = start_chunk;
	while (true) {
		if (!header->used) {
			if (header->size >= chunk_size) {
				// Unused chunk is large enough, go ahead and use it
				return header;
			}
			int ret = try_reclaim(header, chunk_size);
			if (ret == 1) {
				// There's a next chunk, and we were able to reclaim enough unused space
				return header;
			} else if (ret == 2) {
				// We hit the end of allocated chunks, so do some housekeeping
				if (header->prev != NULL) {
					header->prev->next = NULL;
					header = header->prev;
				} else {
					// Should not be true, unless something crazy happened
					header->next = NULL;
				}
			}
		}

		// Allocate new chunk if end
		if (header->next == NULL) {
			void* next = (void*) header + sizeof(chunk_header_t) + ALIGN(header->size, 4);
			if (!ensure_pages(next + chunk_size + sizeof(chunk_header_t))) {
				return NULL;
			}

			chunk_header_t* next_header = memset(next, 0, sizeof(chunk_header_t));
			header->next = next_header;
			next_header->prev = header;
			return next;
		}

		// Find space in between chunks
		uintptr_t end_of_chunk = (uintptr_t) header + sizeof(chunk_header_t) + ALIGN(header->size, 4);
		uintptr_t unused_size = (uintptr_t) header->next - end_of_chunk;
		if (unused_size > chunk_size + sizeof(chunk_header_t)) {
			chunk_header_t* next_header = (chunk_header_t *) end_of_chunk;
			memset(next_header, 0, sizeof(chunk_header_t));
			next_header->next = header->next;
			next_header->prev = header;
			header->next->prev = next_header;
			header->next = next_header;
			return next_header;
		}
		header = header->next;
	}

	return NULL;
}

void* kmalloc(size_t size) {
	if (size == 0) {
		write_serial_str("kmalloc: size was 0, returning NULL...\n");
		return NULL;
	}
	
	chunk_header_t* header = find_unused_chunk(size);
	if (header == NULL) {
		write_serial_str("kmalloc: header was NULL, returning NULL...\n");
		return NULL;
	}
	
	header->used = true;
	header->size = size;
	return (void*) header + sizeof(chunk_header_t);
}

void kfree(void* ptr) {
	if (ptr == NULL) {
		return;
	}
	chunk_header_t* header = ptr - sizeof(chunk_header_t);
	header->used = false;
}

void* krealloc(void* ptr, size_t new_size) {
	if (ptr == NULL) {
		return kmalloc(new_size);
	}

	chunk_header_t* header = ptr - sizeof(chunk_header_t);
	if (header->size >= new_size || try_reclaim(header, new_size)) {
		header->size = new_size;
		return ptr;
	}

	void* new = kmalloc(new_size);
	memcpy(new, ptr, header->size);
	kfree(ptr);
	return new;
}
