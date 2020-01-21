#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/tss.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <string.h>

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
