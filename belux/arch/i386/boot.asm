global _loader
extern kernel_main

MODULEALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

section .data
align 4096
boot_page_directory:
	dd 0x00000083
	times (KERNEL_PAGE_NUMBER - 1) dd 0

	dd 0x00000083
	times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
section .bss
align 16
stack_bottom:
resb 0x4000 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx

	mov ecx, cr4
    or ecx, (1 << 4) ; 4MB pages
	mov cr4, ecx

	mov ecx, cr0
    or ecx, (1 << 31)
	mov cr0, ecx

	; paging is now enabled!

	lea ecx, [.start_higher_half]
	jmp ecx

.start_higher_half:
	mov dword [boot_page_directory], 0
	invlpg [0]

	mov esp, stack_top
	push eax

	; the address of multiboot_info_t passed is physical - need to make it virtual
	add ebx, KERNEL_VIRTUAL_BASE
	push ebx ; multiboot_info_t*

	mov ebp, 0

	call kernel_main
	cli

.hang:
	hlt
	jmp .hang
.end:
