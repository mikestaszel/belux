global _loader
extern kernel_main
 
MODULEALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

; This is the virtual base address of kernel space. It must be used to convert virtual
; addresses into physical addresses until paging is enabled. Note that this is not
; the virtual address where the kernel image itself is loaded -- just the amount that must
; be subtracted from a virtual address to get a physical address.
KERNEL_VIRTUAL_BASE equ 0xC0000000                 ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22) ; Page directory index of kernel's 4MB PTE.

section .data
align 0x1000
boot_page_directory:
	; This page directory entry identity-maps the first 4MB of the 32-bit physical address space.
	; All bits are clear except the following:
	; bit 7: PS The kernel page is 4MB.
	; bit 1: RW The kernel page is read/write.
	; bit 0: P  The kernel page is present.
	dd 0x00000083
	times (KERNEL_PAGE_NUMBER - 1) dd 0 ; pages before kernel space.
	; This page directory entry defines a 4MB page containing the kernel.
	dd 0x00000083
	times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0 ; pages after the kernel image.

section .text
align 4
multiboot_header:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

STACKSIZE equ 0x4000

_loader:
	mov ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx ; Load Page Directory Base register

	mov ecx, cr4
	or ecx, 0x00000010 ; Set PSE bit in CR4 to enable 4MB pages.
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000000 ; Set PG bit in CR0 to enable paging.
	mov cr0, ecx

	; paging is now enabled!

	lea ecx, [higher_half]
	jmp ecx

higher_half:
	; Unmap the identity-mapped first 4MB of physical address space. It should not be needed anymore.
	mov dword [boot_page_directory], 0
	
	invlpg [0] ; invalidate any TLB references to virtual address 0

	; NOTE: The first 4MB of physical address space is
	; mapped starting at KERNEL_VIRTUAL_BASE. Everything is linked to this address, so no more
	; position-independent code or should be necessary.
	mov esp, stack + STACKSIZE
	push eax ; magic number

	; the address of multiboot_info_t passed is physical - need to make it virtual
	add ebx, KERNEL_VIRTUAL_BASE
	push ebx ; multiboot_info_t*

	call kernel_main
	hlt

section .bss
align 32
stack:
	resb STACKSIZE
