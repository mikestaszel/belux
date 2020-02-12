#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

extern void gdt_flush(uintptr_t);
void gdt_install(void);
void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);

typedef struct {
	uint16_t limit_low; // the lower 16 bits of the limit
	uint16_t base_low; // the lower 16 bits of the base
	uint8_t base_middle; // the next 8 bits of the base
	uint8_t access; // access flags to determine what ring this segment can be used in
	uint8_t granularity;
	uint8_t base_high; // the last 8 bits of the base
} __attribute__((packed)) gdt_entry_t;

typedef struct {
	uint16_t limit; // the upper 16 bits of all selector limits
	uintptr_t base; // the address of the first gdt_entry_t.
} __attribute__((packed)) gdt_pointer_t;

static struct {
    gdt_entry_t entries[6];
    gdt_pointer_t pointer;
    tss_entry_t tss;
} gdt __attribute__((used));

#endif
