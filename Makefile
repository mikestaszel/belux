kernel:
	nasm -felf32 boot.asm -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o belux.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

iso: kernel
	cp belux.bin iso/boot/belux.bin
	grub-mkrescue -o belux.iso iso

run: iso
	qemu-system-i386 -cdrom belux.iso

clean:
	rm -f boot.o kernel.o belux.bin belux.iso iso/boot/belux.bin

all: iso
