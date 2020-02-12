#include <stdint.h>

void outb(unsigned short port, unsigned char data) {
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

unsigned char inb(unsigned short port) {
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

short inw(unsigned short port) {
	short ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}
