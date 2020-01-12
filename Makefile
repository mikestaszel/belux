CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CC:=i686-elf-gcc

ARCHDIR:=kernel/arch/i386

ARCH_OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(ARCHDIR)/boot.o \
$(ARCHDIR)/tty.o \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(ARCHDIR)/boot.o \
$(ARCHDIR)/tty.o \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

.PHONY: run clean all

iso/boot/belux.bin: $(ARCH_OBJS)
	$(CC) -c kernel/kernel/kernel.c -o kernel/kernel/kernel.o $(CFLAGS) -std=gnu11 -Ikernel/include
	$(CC) -T $(ARCHDIR)/linker.ld -o iso/boot/belux.bin $(CFLAGS) -nostdlib $(LINK_LIST) kernel/kernel/kernel.o -lgcc

$(ARCHDIR)/boot.o: $(ARCHDIR)/boot.asm
	nasm -felf32 $< -o $@

$(ARCHDIR)/crti.o: $(ARCHDIR)/crti.asm
	nasm -felf32 $< -o $@

$(ARCHDIR)/crtn.o: $(ARCHDIR)/crtn.asm
	nasm -felf32 $< -o $@

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(ARCHDIR)/tty.o: $(ARCHDIR)/tty.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/include

belux.iso: iso/boot/belux.bin
	grub-mkrescue -o belux.iso iso/

run: belux.iso
	qemu-system-i386 -cdrom belux.iso

clean:
	$(RM) $(ARCH_OBJS)
	$(RM) kernel/kernel/kernel.o iso/boot/belux.bin belux.iso

all: belux.iso
