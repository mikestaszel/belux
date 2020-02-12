#include <string.h>
#include <stdint.h>
#include <kernel/tss.h>
#include <kernel/gdt.h>

#define GDTENTRY(X) (gdt.entries[(X)])

void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
	GDTENTRY(num).base_low = (base & 0xFFFF);
	GDTENTRY(num).base_middle = (base >> 16) & 0xFF;
	GDTENTRY(num).base_high = (base >> 24) & 0xFF;
	GDTENTRY(num).limit_low = (limit & 0xFFFF);
	GDTENTRY(num).granularity = (limit >> 16) & 0X0F;
	GDTENTRY(num).granularity |= (gran & 0xF0);
	GDTENTRY(num).access = access;
}

void gdt_install(void) {
	gdt_pointer_t* gdtp = &gdt.pointer;
	gdtp->limit = sizeof gdt.entries - 1;
	gdtp->base = (uintptr_t) & GDTENTRY(0);

	gdt_set_gate(0, 0, 0, 0, 0);                // NULL segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	write_tss(5, 0x10, 0x0);

	gdt_flush((uintptr_t)gdtp);
	tss_flush();
}

void set_kernel_stack(uintptr_t stack) {
	gdt.tss.esp0 = stack;
}
