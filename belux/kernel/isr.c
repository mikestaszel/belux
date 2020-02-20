#include <stdint.h>
#include <kernel/io.h>
#include <kernel/isr.h>
#include <stdio.h>

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler) {
	interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs) {
	uint8_t int_no = regs.int_no & 0xFF;
	if (interrupt_handlers[int_no] != 0) {
		isr_t handler = interrupt_handlers[int_no];
		handler(&regs);
	}
	else {
		printf("unhandled interrupt, cannot continue: %x\n", int_no);
		while(1);
	}
}

void irq_handler(registers_t regs) {
	if (regs.int_no >= 40) {
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);

	if (interrupt_handlers[regs.int_no] != 0) {
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(&regs);
	}

}
