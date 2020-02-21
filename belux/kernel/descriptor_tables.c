#include <string.h>
#include <stdint.h>
#include <kernel/io.h>
#include <kernel/descriptor_tables.h>

/* TSS */
void write_tss(int32_t num, uint16_t ss0, uint32_t esp0) {
	tss_entry_t* tss = &gdt.tss;
	uintptr_t base = (uintptr_t)tss;
	uintptr_t limit = base + sizeof *tss;

	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(tss, 0x0, sizeof *tss);

	tss->ss0 = ss0;
	tss->esp0 = esp0;
	tss->cs = 0x0b;
	tss->ss = 0x13;
	tss->ds = 0x13;
	tss->es = 0x13;
	tss->fs = 0x13;
	tss->gs = 0x13;

	tss->iomap_base = sizeof *tss;
}

/* IDT */
void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
	IDTENTRY(num).base_low = ((uintptr_t) base & 0xFFFF);
	IDTENTRY(num).base_high = ((uintptr_t) base >> 16) & 0xFFFF;
	IDTENTRY(num).sel = sel;
	IDTENTRY(num).zero = 0;
	IDTENTRY(num).flags = flags | 0x60;
}

void idt_init() {
	extern int load_idt();
	extern int irq0();
	extern int irq1();
	extern int irq2();
	extern int irq3();
	extern int irq4();
	extern int irq5();
	extern int irq6();
	extern int irq7();
	extern int irq8();
	extern int irq9();
	extern int irq10();
	extern int irq11();
	extern int irq12();
	extern int irq13();
	extern int irq14();
	extern int irq15();

	unsigned long irq0_address;
	unsigned long irq1_address;
	unsigned long irq2_address;
	unsigned long irq3_address;
	unsigned long irq4_address;
	unsigned long irq5_address;
	unsigned long irq6_address;
	unsigned long irq7_address;
	unsigned long irq8_address;
	unsigned long irq9_address;
	unsigned long irq10_address;
	unsigned long irq11_address;
	unsigned long irq12_address;
	unsigned long irq13_address;
	unsigned long irq14_address;
	unsigned long irq15_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	// remapping the PIC:
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 40);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	// enable all interrupts:
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	irq0_address = (unsigned long)irq0; 
	IDT[32].offset_lowerbits = irq0_address & 0xffff;
	IDT[32].selector = 0x08;
	IDT[32].zero = 0;
	IDT[32].type_attr = 0x8e;
	IDT[32].offset_higherbits = (irq0_address & 0xffff0000) >> 16;

	irq1_address = (unsigned long)irq1; 
	IDT[33].offset_lowerbits = irq1_address & 0xffff;
	IDT[33].selector = 0x08;
	IDT[33].zero = 0;
	IDT[33].type_attr = 0x8e;
	IDT[33].offset_higherbits = (irq1_address & 0xffff0000) >> 16;

	irq2_address = (unsigned long)irq2; 
	IDT[34].offset_lowerbits = irq2_address & 0xffff;
	IDT[34].selector = 0x08;
	IDT[34].zero = 0;
	IDT[34].type_attr = 0x8e;
	IDT[34].offset_higherbits = (irq2_address & 0xffff0000) >> 16;

	irq3_address = (unsigned long)irq3; 
	IDT[35].offset_lowerbits = irq3_address & 0xffff;
	IDT[35].selector = 0x08;
	IDT[35].zero = 0;
	IDT[35].type_attr = 0x8e;
	IDT[35].offset_higherbits = (irq3_address & 0xffff0000) >> 16;

	irq4_address = (unsigned long)irq4; 
	IDT[36].offset_lowerbits = irq4_address & 0xffff;
	IDT[36].selector = 0x08;
	IDT[36].zero = 0;
	IDT[36].type_attr = 0x8e;
	IDT[36].offset_higherbits = (irq4_address & 0xffff0000) >> 16;

	irq5_address = (unsigned long)irq5; 
	IDT[37].offset_lowerbits = irq5_address & 0xffff;
	IDT[37].selector = 0x08;
	IDT[37].zero = 0;
	IDT[37].type_attr = 0x8e;
	IDT[37].offset_higherbits = (irq5_address & 0xffff0000) >> 16;

	irq6_address = (unsigned long)irq6; 
	IDT[38].offset_lowerbits = irq6_address & 0xffff;
	IDT[38].selector = 0x08;
	IDT[38].zero = 0;
	IDT[38].type_attr = 0x8e;
	IDT[38].offset_higherbits = (irq6_address & 0xffff0000) >> 16;

	irq7_address = (unsigned long)irq7; 
	IDT[39].offset_lowerbits = irq7_address & 0xffff;
	IDT[39].selector = 0x08;
	IDT[39].zero = 0;
	IDT[39].type_attr = 0x8e;
	IDT[39].offset_higherbits = (irq7_address & 0xffff0000) >> 16;

	irq8_address = (unsigned long)irq8; 
	IDT[40].offset_lowerbits = irq8_address & 0xffff;
	IDT[40].selector = 0x08;
	IDT[40].zero = 0;
	IDT[40].type_attr = 0x8e;
	IDT[40].offset_higherbits = (irq8_address & 0xffff0000) >> 16;

	irq9_address = (unsigned long)irq9; 
	IDT[41].offset_lowerbits = irq9_address & 0xffff;
	IDT[41].selector = 0x08;
	IDT[41].zero = 0;
	IDT[41].type_attr = 0x8e;
	IDT[41].offset_higherbits = (irq9_address & 0xffff0000) >> 16;

	irq10_address = (unsigned long)irq10; 
	IDT[42].offset_lowerbits = irq10_address & 0xffff;
	IDT[42].selector = 0x08;
	IDT[42].zero = 0;
	IDT[42].type_attr = 0x8e;
	IDT[42].offset_higherbits = (irq10_address & 0xffff0000) >> 16;

	irq11_address = (unsigned long)irq11; 
	IDT[43].offset_lowerbits = irq11_address & 0xffff;
	IDT[43].selector = 0x08;
	IDT[43].zero = 0;
	IDT[43].type_attr = 0x8e;
	IDT[43].offset_higherbits = (irq11_address & 0xffff0000) >> 16;

	irq12_address = (unsigned long)irq12; 
	IDT[44].offset_lowerbits = irq12_address & 0xffff;
	IDT[44].selector = 0x08;
	IDT[44].zero = 0;
	IDT[44].type_attr = 0x8e;
	IDT[44].offset_higherbits = (irq12_address & 0xffff0000) >> 16;

	irq13_address = (unsigned long)irq13; 
	IDT[45].offset_lowerbits = irq13_address & 0xffff;
	IDT[45].selector = 0x08;
	IDT[45].zero = 0;
	IDT[45].type_attr = 0x8e;
	IDT[45].offset_higherbits = (irq13_address & 0xffff0000) >> 16;

	irq14_address = (unsigned long)irq14; 
	IDT[46].offset_lowerbits = irq14_address & 0xffff;
	IDT[46].selector = 0x08;
	IDT[46].zero = 0;
	IDT[46].type_attr = 0x8e;
	IDT[46].offset_higherbits = (irq14_address & 0xffff0000) >> 16;

	irq15_address = (unsigned long)irq15; 
	IDT[47].offset_lowerbits = irq15_address & 0xffff;
	IDT[47].selector = 0x08;
	IDT[47].zero = 0;
	IDT[47].type_attr = 0x8e;
	IDT[47].offset_higherbits = (irq15_address & 0xffff0000) >> 16;

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16;

	load_idt(idt_ptr);
}

void idt_install(void) {
	idt_pointer_t* idtp = &idt.pointer;
	idtp->limit = sizeof idt.entries - 1;
	idtp->base = (uintptr_t) & IDTENTRY(0);
	memset(&IDTENTRY(0), 0, sizeof idt.entries);

	idt_init();
}

/* GDT */
void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
	GDTENTRY(num).base_low = (base & 0xFFFF);
	GDTENTRY(num).base_middle = (base >> 16) & 0xFF;
	GDTENTRY(num).base_high = (base >> 24) & 0xFF;
	GDTENTRY(num).limit_low = (limit & 0xFFFF);
	GDTENTRY(num).granularity = (limit >> 16) & 0X0F;
	GDTENTRY(num).granularity |= (gran & 0xF0);
	GDTENTRY(num).access = access;
}

void gdt_install(void) {
	gdt_pointer_t* gdtp = &gdt.pointer;
	gdtp->limit = sizeof gdt.entries - 1;
	gdtp->base = (uintptr_t) & GDTENTRY(0);

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	write_tss(5, 0x10, 0x0);

	gdt_flush((uintptr_t) gdtp);
	tss_flush();
}

void set_kernel_stack(uintptr_t stack) {
	gdt.tss.esp0 = stack;
}
