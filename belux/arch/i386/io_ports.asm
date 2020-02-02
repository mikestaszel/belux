global inb
global outb

inb:
	mov edx, [esp + 4]
	in al, dx
	ret

outb:
	mov edx, [esp + 4]
	mov al, [esp + 8]
	out dx, al
	ret
