global read_port
global write_port
global tss_flush
global gdt_flush

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	ret

tss_flush:
	mov ax, 0x2B
	ltr ax
	ret

gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush		; far jump to populate cs

.flush:
	ret
