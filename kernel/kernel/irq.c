#include <kernel/io_ports.h>
#include <stdio.h>

// irq.c
// from: https://wiki.osdev.org/Interrupts_tutorial

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
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

void irq0_handler(void) {
	write_port(0x20, 0x20);
}

static char shift_pressed = 0;

void irq1_handler(void) {
    // keyboard!
    write_port(0x20, 0x20);

    unsigned char status = read_port(0x64);
	
    if (status & 0x01) {
        unsigned char scancode = read_port(0x60);

        if (scancode & 0x80) {
            // key is released
            if (scancode == 0xaa || scancode == 0xb6) {
                shift_pressed = 0;
                return;
            }
        }
        else {
            if (scancode == 42 || scancode == 54) {
                shift_pressed = 1;
                return;
            }

            if (shift_pressed) {
                putchar(keyboard_map_shift[scancode]);
            }
            else {
                putchar(keyboard_map[scancode]);
            }
        }
    }
}

void irq2_handler(void) {
	write_port(0x20, 0x20);
	printf("IRQ 2!!!");
}

void irq3_handler(void) {
	write_port(0x20, 0x20);
	printf("IRQ 3!!!");
}

void irq4_handler(void) {
	write_port(0x20, 0x20);
	printf("IRQ 4!!!");
}

void irq5_handler(void) {
    write_port(0x20, 0x20);
    printf("IRQ 5!!!");
}

void irq6_handler(void) {
    write_port(0x20, 0x20);
    printf("IRQ 6!!!");
}

void irq7_handler(void) {
    write_port(0x20, 0x20);
    printf("IRQ 7!!!");
}

void irq8_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 8!!!");
}

void irq9_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 9!!!");
}

void irq10_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 10!!!");
}

void irq11_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 11!!!");
}

void irq12_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 12!!!");
}

void irq13_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 13!!!");
}

void irq14_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 14!!!");
}

void irq15_handler(void) {
    write_port(0xA0, 0x20);
    write_port(0x20, 0x20);
    printf("IRQ 15!!!");
}
