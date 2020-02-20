#ifndef _KERNEL_DESCRIPTOR_TABLES_H
#define _KERNEL_DESCRIPTOR_TABLES_H

#define GDTENTRY(X) (gdt.entries[(X)])
#define IDTENTRY(X) (idt.entries[(X)])

/* TSS */
typedef struct tss_entry {
	uint32_t prev_tss;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap_base;
} __attribute__ ((packed)) tss_entry_t;

/* IDT */
#define IDT_SIZE 256

extern void idt_init();
void idt_install(void);

typedef void (*idt_gate_t)(void);

typedef struct {
	uint16_t base_low;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t limit;
	uintptr_t base;
} __attribute__((packed)) idt_pointer_t;

static struct {
	idt_entry_t entries[256];
	idt_pointer_t pointer;
} idt __attribute__((used));

struct IDT_entry {
	uint16_t offset_lowerbits; // offset bits 0..15
	uint16_t selector; // a code segment selector in GDT or LDT
	uint8_t zero; // unused, set to 0
	uint8_t type_attr; // type and attributes
	uint16_t offset_higherbits; // offset bits 16..31
};

struct IDT_entry IDT[IDT_SIZE];

/* GDT */
typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
	uint16_t limit;
	uintptr_t base;
} __attribute__((packed)) gdt_pointer_t;

static struct {
    gdt_entry_t entries[6];
    gdt_pointer_t pointer;
    tss_entry_t tss;
} gdt __attribute__((used));

extern void tss_flush(void);
void write_tss(int32_t num, uint16_t ss0, uint32_t esp0);

extern void gdt_flush(uintptr_t);
void gdt_install(void);
void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);

#endif
