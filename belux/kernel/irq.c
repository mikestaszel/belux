#include <kernel/io_ports.h>
#include <stdio.h>
#include <drivers/keyboard.h>

// from: https://wiki.osdev.org/Interrupts_tutorial

void irq0_handler(void) {
	outb(0x20, 0x20);
}

void irq1_handler(void) {
	keyboard_handler();
}

void irq2_handler(void) {
	outb(0x20, 0x20);
	printf("IRQ 2!!!");
}

void irq3_handler(void) {
	outb(0x20, 0x20);
	printf("IRQ 3!!!");
}

void irq4_handler(void) {
	outb(0x20, 0x20);
	printf("IRQ 4!!!");
}

void irq5_handler(void) {
	outb(0x20, 0x20);
	printf("IRQ 5!!!");
}

void irq6_handler(void) {
	outb(0x20, 0x20);
	printf("IRQ 6!!!");
}

void irq7_handler(void) {
	outb(0x20, 0x20);
	printf("IRQ 7!!!");
}

void irq8_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 8!!!");
}

void irq9_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 9!!!");
}

void irq10_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 10!!!");
}

void irq11_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 11!!!");
}

void irq12_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 12!!!");
}

void irq13_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 13!!!");
}

void irq14_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 14!!!");
}

void irq15_handler(void) {
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
	printf("IRQ 15!!!");
}
