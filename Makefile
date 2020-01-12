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
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(ARCHDIR)/boot.o \
$(ARCHDIR)/tty.o \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

ISO_FILE=belux.iso
KERNEL_FILE=iso/boot/belux.bin

.PHONY: run clean all

$(KERNEL_FILE): $(ARCH_OBJS)
	$(CC) -c kernel/kernel/kernel.c -o kernel/kernel/kernel.o $(CFLAGS) -std=gnu11 -Ikernel/include
	$(CC) -T $(ARCHDIR)/linker.ld -o $(KERNEL_FILE) $(CFLAGS) -nostdlib $(LDFLAGS) $(LINK_LIST) kernel/kernel/kernel.o -lgcc

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

$(ISO_FILE): $(KERNEL_FILE)
	grub-mkrescue -o $(ISO_FILE) iso/

run: $(ISO_FILE)
	qemu-system-i386 -cdrom $(ISO_FILE)

clean:
	$(RM) $(ARCH_OBJS)
	$(RM) kernel/kernel/kernel.o $(KERNEL_FILE) $(ISO_FILE)

all: $(ISO_FILE)
