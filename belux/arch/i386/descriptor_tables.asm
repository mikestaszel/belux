align 4
global gdt_flush
global load_idt
global tss_flush

gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush
.flush:
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

tss_flush:
	mov ax, 0x2B
	ltr ax
	ret
