#include <kernel/io_ports.h>
#include <stdio.h>

// irq.c
// from: https://wiki.osdev.org/Interrupts_tutorial

unsigned char keyboard_map[128] =
{
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

void irq0_handler(void) {
	write_port(0x20, 0x20);
}

void irq1_handler(void) {
    // keyboard!
    write_port(0x20, 0x20);
    unsigned char status = read_port(0x64);
    char keycode;
	
    if (status & 0x01) {
        keycode = read_port(0x60);
        if (keycode < 0)
            return;

        if (keycode == 0x1C) {
            // ENTER KEY!
            printf("\n");
            return;
        }

        putchar(keyboard_map[(unsigned char) keycode]);
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
