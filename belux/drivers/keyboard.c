#include <stdint.h>
#include <string.h>
#include <kernel/isr.h>
#include <kernel/io.h>
#include <drivers/keyboard.h>
#include <kernel/shell.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define L_SHIFT_RELEASE 0xAA
#define R_SHIFT_RELEASE 0xB6
#define ARROW_UP 0x48
#define ARROW_DOWN 0x50

#define ASCII_MAX 58

const char ascii_upper[ASCII_MAX] = {
	0, 0, '!', '@', '#', '$', '%', '^',
	'&', '*', '(', ')', '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y',
	'U', 'I', 'O', 'P', '{', '}', 0, 0, 'A', 'S', 'D', 'F', 'G',
	'H', 'J', 'K', 'L', ':', '"', '~', 0, '\\', 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' '
};
const char ascii_lower[ASCII_MAX] = {
	0, 0, '1', '2', '3', '4', '5', '6',
	'7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y',
	'u', 'i', 'o', 'p', '[', ']', 0, 0, 'a', 's', 'd', 'f', 'g',
	'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/', 0, 0, 0, 0
};

static unsigned char shift_pressed = 0;

void irq_callback(registers_t regs) {
	unsigned char c = inb(0x60);
	if (c == L_SHIFT || c == R_SHIFT) {
		shift_pressed = 1;
	} else if (c == L_SHIFT_RELEASE || c == R_SHIFT_RELEASE) {
		shift_pressed = 0;
	} else if (c == BACKSPACE) {
		key_buffer_backspace();
	} else if (c == ENTER) {
		key_buffer_return();
	} else if (c == ARROW_UP) {
		return;
	} else if (c == ARROW_DOWN) {
		return;
	}

	if (c > ASCII_MAX) {
		return;
	} else if (!shift_pressed && ascii_lower[c]) {
		key_buffer_append(ascii_lower[c]);
	} else if (ascii_upper[c]) {
		key_buffer_append(ascii_upper[c]);
	}
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, &irq_callback);
}
