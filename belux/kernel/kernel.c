#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/tss.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/serial.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kernel/timer.h>
#include <drivers/keyboard.h>
#include <string.h>

// The linker gives us these values:
void _kernel_virtual_start(void);
void _kernel_virtual_end(void);

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

	printf("mem_lower = %uKB, mem_upper = %uKB\n", (unsigned) mbt->mem_lower, (unsigned) mbt->mem_upper);
	
	// init_timer(10);
	init_keyboard();

	printf("_kernel_virtual_start: 0x%x\n", &_kernel_virtual_start);
	printf("_kernel_virtual_end: 0x%x\n", &_kernel_virtual_end);

	// unsigned int* ptr = (unsigned int*)0xA0000000;
	// unsigned int do_page_fault = *ptr;

	while(1);
}
