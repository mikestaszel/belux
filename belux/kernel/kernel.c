#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/tss.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/serial.h>
#include <kernel/multiboot.h>
#include <string.h>

// multiboot_info_t helper to check if the bit BIT in FLAGS is set.
#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))


// Our entrypoint.
void kernel_main(multiboot_info_t* mbt, unsigned int magic) {
	gdt_install();
	idt_install();

	serial_initialize();
	write_serial_str("Hello, world!");

	terminal_initialize();

	// TODO: Don't forget to make all addresses pointing to memory locations in the Multiboot info structure also virtual.

	// Are mem_* valid?
	if (CHECK_FLAG(mbt->flags, 0)) {
		printf("mem_lower = %uKB, mem_upper = %uKB\n", (unsigned) mbt->mem_lower, (unsigned) mbt->mem_upper);
	}

	// Is boot_device valid? 
	// if (CHECK_FLAG (mbt->flags, 1)) {
	// 	printf("boot_device = %x\n", (unsigned) mbt->boot_device);
	// }

	// Is the command line passed?
	// if (CHECK_FLAG (mbt->flags, 2)) {
	// 	printf("cmdline = %s\n", (char *) mbt->cmdline);
	// }

	// printf("Hello, world!\n");
	// printf("A second line!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nLAST LINE!\n");
	// printf("OH NO!\n");
	// printf("AND ANOTHER ONE!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nWOAH!\n");
	// printf("Scrolling!\n");
	// printf("yo!\n");
	while(1);
}
