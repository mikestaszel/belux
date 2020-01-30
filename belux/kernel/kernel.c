#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/tss.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/serial.h>
#include <kernel/multiboot.h>
#include <string.h>

void kernel_main(multiboot_info_t* mbt, unsigned int magic) {
	gdt_install();
	idt_install();

	serial_initialize();
	write_serial_str("Hello, world!");

	terminal_initialize();

	printf("Hello, world!\n");
	printf("A second line!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nLAST LINE!\n");
	printf("OH NO!\n");
	printf("AND ANOTHER ONE!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nWOAH!\n");
	printf("Scrolling!\n");
	printf("yo!\n");
	while(1);
}
