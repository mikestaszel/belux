#include <stdint.h>
#include <kernel/isr.h>
#include <kernel/io.h>
#include <stdio.h>
#include <drivers/keyboard.h>

unsigned char keyboard_map[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
	'9', '0', '-', '=', '\b', /* Backspace */
	'\t', /* Tab */
	'q', 'w', 'e', 'r',   /* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
	0,  /* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
	'\'', '`',   0,        /* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
	'm', ',', '.', '/',   0,              /* Right shift */
	'*',
	0,  /* Alt */
	' ',  /* Space bar */
	0,  /* Caps lock */
	0,  /* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,  /* < ... F10 */
	0,  /* 69 - Num lock*/
	0,  /* Scroll Lock */
	0,  /* Home key */
	0,  /* Up Arrow */
	0,  /* Page Up */
	'-',
	0,  /* Left Arrow */
	0,
	0,  /* Right Arrow */
	'+',
	0,  /* 79 - End key*/
	0,  /* Down Arrow */
	0,  /* Page Down */
	0,  /* Insert Key */
	0,  /* Delete Key */
	0,   0,   0,
	0,  /* F11 Key */
	0,  /* F12 Key */
	0,  /* All other keys are undefined */
};

unsigned char keyboard_map_shift[128] = {
	0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
	'(', ')', '_', '+', '\b', /* Backspace */
	'\t',         /* Tab */
	'Q', 'W', 'E', 'R',   /* 19 */
	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
	0,          /* 29   - Control */
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
	'\"', '~',   0,        /* Left shift */
	'|', 'Z', 'X', 'C', 'V', 'B', 'N',            /* 49 */
	'M', '<', '>', '?',   0,              /* Right shift */
	'*',
	0,  /* Alt */
	' ',  /* Space bar */
	0,  /* Caps lock */
	0,  /* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,  /* < ... F10 */
	0,  /* 69 - Num lock*/
	0,  /* Scroll Lock */
	0,  /* Home key */
	0,  /* Up Arrow */
	0,  /* Page Up */
	'-',
	0,  /* Left Arrow */
	0,
	0,  /* Right Arrow */
	'+',
	0,  /* 79 - End key*/
	0,  /* Down Arrow */
	0,  /* Page Down */
	0,  /* Insert Key */
	0,  /* Delete Key */
	0,   0,   0,
	0,  /* F11 Key */
	0,  /* F12 Key */
	0,  /* All other keys are undefined */
};

static char shift_pressed = 0;

void keyboard_handler() {
	// outb(0x20, 0x20); // ack

	unsigned char status = inb(0x64);
	
	if (status & 0x01) {
		unsigned char scancode = inb(0x60);

		if (scancode & 0x80) {
			// key is released
			if (scancode == 0xaa || scancode == 0xb6) {
				shift_pressed = 0;
				return;
			}
		}
		else {
			// is shift pressed?
			if (scancode == 42 || scancode == 54) {
				shift_pressed = 1;
				return;
			}

			unsigned char c;

			if (shift_pressed) {
				c = keyboard_map_shift[scancode];
			}
			else {
				c = keyboard_map[scancode];
			}
			
			putchar(c);
		}
	}
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, &keyboard_handler);
}
