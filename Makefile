CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CC:=i686-elf-gcc

ARCHDIR:=kernel/arch/i386

iso/boot/belux.bin:
	nasm -felf32 $(ARCHDIR)/boot.asm -o $(ARCHDIR)/boot.o
	$(CC) -c $(ARCHDIR)/tty.c -o $(ARCHDIR)/tty.o $(CFLAGS) -std=gnu11 -Ikernel/include
	$(CC) -c kernel/kernel/kernel.c -o kernel/kernel/kernel.o $(CFLAGS) -std=gnu11 -Ikernel/include
	$(CC) -T $(ARCHDIR)/linker.ld -o iso/boot/belux.bin $(CFLAGS) -nostdlib $(ARCHDIR)/boot.o $(ARCHDIR)/tty.o kernel/kernel/kernel.o -lgcc

iso: iso/boot/belux.bin
	grub-mkrescue -o belux.iso iso

run: iso
	qemu-system-i386 -cdrom belux.iso

clean:
	rm -f boot.o kernel.o belux.bin belux.iso iso/boot/belux.bin

all: iso
