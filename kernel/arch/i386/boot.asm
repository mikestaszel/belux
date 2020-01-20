MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text

jmp _start

gdt:

gdt_null:
	dq 0

gdt_code:
	dw 0FFFFh
	dw 0

	db 0
	db 10011010b
	db 11001111b
	db 0

gdt_data:
	dw 0FFFFh
	dw 0

	db 0
	db 10010010b
	db 11001111b
	db 0

gdt_end:

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt

_start:
	cli
	lgdt [gdt_desc]
	mov esp, stack_top
	extern kernel_main
	call kernel_main
	cli
.hang:	hlt
	jmp .hang
.end:

global _start:function (_start.end - _start)
