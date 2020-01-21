global read_port
global write_port
global tss_flush

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
