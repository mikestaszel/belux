#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/tss.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/idt_init.h>
#include <string.h>

#define GDTENTRY(X) (gdt.entries[(X)])

void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
	/* Base Address */
	GDTENTRY(num).base_low = (base & 0xFFFF);
	GDTENTRY(num).base_middle = (base >> 16) & 0xFF;
	GDTENTRY(num).base_high = (base >> 24) & 0xFF;
	/* Limits */
	GDTENTRY(num).limit_low = (limit & 0xFFFF);
	GDTENTRY(num).granularity = (limit >> 16) & 0X0F;
	/* Granularity */
	GDTENTRY(num).granularity |= (gran & 0xF0);
	/* Access flags */
	GDTENTRY(num).access = access;
}

void gdt_install(void) {
	gdt_pointer_t *gdtp = &gdt.pointer;
	gdtp->limit = sizeof gdt.entries - 1;
	gdtp->base = (uintptr_t)&GDTENTRY(0);

	gdt_set_gate(0, 0, 0, 0, 0);                /* NULL segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User code */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User data */

	write_tss(5, 0x10, 0x0);

	/* Go go go */
	gdt_flush((uintptr_t)gdtp);
	tss_flush();
}

static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0) {
	tss_entry_t * tss = &gdt.tss;
	uintptr_t base = (uintptr_t)tss;
	uintptr_t limit = base + sizeof *tss;

	/* Add the TSS descriptor to the GDT */
	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(tss, 0x0, sizeof *tss);

	tss->ss0 = ss0;
	tss->esp0 = esp0;
	tss->cs = 0x0b;
	tss->ss = 0x13;
	tss->ds = 0x13;
	tss->es = 0x13;
	tss->fs = 0x13;
	tss->gs = 0x13;

	tss->iomap_base = sizeof *tss;
}

void set_kernel_stack(uintptr_t stack) {
	gdt.tss.esp0 = stack;
}

#define IDTENTRY(X) (idt.entries[(X)])

typedef void (*idt_gate_t)(void);

void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
	IDTENTRY(num).base_low = ((uintptr_t)base & 0xFFFF);
	IDTENTRY(num).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	IDTENTRY(num).sel = sel;
	IDTENTRY(num).zero = 0;
	IDTENTRY(num).flags = flags | 0x60;
}

void idt_install(void) {
	idt_pointer_t* idtp = &idt.pointer;
	idtp->limit = sizeof idt.entries - 1;
	idtp->base = (uintptr_t)&IDTENTRY(0);
	memset(&IDTENTRY(0), 0, sizeof idt.entries);

	idt_init();
}

void kernel_main() {
	gdt_install();
	idt_install();
	terminal_initialize();

	printf("Hello, world!\n");
	printf("A second line!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nLAST LINE!\n");
	printf("OH NO!\n");
	printf("AND ANOTHER ONE!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nWOAH!\n");
	printf("Scrolling!\n");
	printf("yo!\n");
	while(1);
}
