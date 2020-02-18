#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kernel/descriptor_tables.h>
#include <kernel/serial.h>
#include <kernel/multiboot.h>
#include <kernel/timer.h>
#include <kernel/tty.h>
#include <kernel/shell.h>
#include <drivers/keyboard.h>

#define KERNEL_OFFSET 0x200000

void kernel_main(multiboot_info_t* mbt, unsigned int magic) {
	gdt_install();
	idt_install();

	extern void* malloc_memory_start;
	extern void* malloc_memory_end;

	malloc_memory_start = (void *) 0x100000 + KERNEL_OFFSET;
	malloc_memory_end = malloc_memory_start + (mbt->mem_upper * 0x400) - KERNEL_OFFSET;

	init_timer(10);
	init_keyboard();

	init_serial();
	write_serial_str("Hello, world!\n");

	terminal_initialize();

	shell_init(0);

	while (1) {
		shell_read();
		key_buffer_print();
	}
}
