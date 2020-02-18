#include <string.h>
#include <kernel/io.h>
#include <kernel/serial.h>

#define PORT 0x3f8 // COM1

void init_serial() {
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x80);
	outb(PORT + 0, 0x03);
	outb(PORT + 1, 0x00);
	outb(PORT + 3, 0x03);
	outb(PORT + 2, 0xC7);
	outb(PORT + 4, 0x0B);
}

int is_transmit_empty() {
	return inb(PORT + 5) & 0x20;
}

void write_serial(char c) {
	while (is_transmit_empty() == 0); // wait
	outb(PORT, c);
}

void write_serial_str(char* input) {
	for (size_t i = 0; i < strlen(input); i++) {
		write_serial(input[i]);
	}
}

int serial_received() {
	return inb(PORT + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0); // wait
	return inb(PORT);
}
