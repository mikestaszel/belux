#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/io_ports.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t get_cursor_position(void) {
	// With this code, you get: pos = y * VGA_WIDTH + x.
	// To obtain the coordinates, just calculate: y = pos / VGA_WIDTH; x = pos % VGA_WIDTH;
	uint16_t pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;
	return pos;
}

void terminal_blank() {
	// blank out the screen:
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xC00B8000;

	terminal_blank();
	enable_cursor(0, 15);
	update_cursor(0, 0);
}

void terminal_scroll() {
	terminal_row = VGA_HEIGHT - 1;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	if (terminal_row == VGA_HEIGHT) {
		terminal_scroll();
	}

	// newline support:
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		if (terminal_row == VGA_HEIGHT) {
			terminal_scroll();
		}
		update_cursor(terminal_column, terminal_row);
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

	// ++terminal_column and ++terminal_row increment before checking:
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_scroll();
		}
	}
	update_cursor(terminal_column, terminal_row);
}
