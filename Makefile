CFLAGS?=-O0 -std=gnu11
CPPFLAGS?=
LDFLAGS?=
LIBS?=
NASMFLAGS?=

CC:=i686-elf-gcc
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
NASMFLAGS:=-felf32 -w+orphan-labels

KERNELINCLUDE:=-Ibelux/include -Ibelux/libck/include

ARCH_DIR:=belux/arch/i386
LIBCK_DIR:=belux/libck
KERNEL_DIR:=belux/kernel
DRIVERS_DIR:=belux/drivers

ARCH_OBJS=\
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(ARCH_DIR)/boot.o \
$(ARCH_DIR)/descriptor_tables.o \
$(ARCH_DIR)/interrupts.o \
$(ARCH_DIR)/io.o \
$(ARCH_DIR)/tty.o \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

LIBCK_OBJS=\
$(LIBCK_DIR)/stdio.o \
$(LIBCK_DIR)/string.o \

KERNEL_OBJS=\
$(KERNEL_DIR)/isr.o \
$(KERNEL_DIR)/descriptor_tables.o \
$(KERNEL_DIR)/timer.o \
$(KERNEL_DIR)/kmalloc.o \
$(KERNEL_DIR)/mmu.o \
$(KERNEL_DIR)/shell.o \
$(KERNEL_DIR)/serial.o \
$(KERNEL_DIR)/kernel.o \

DRIVER_OBJS=\
$(DRIVERS_DIR)/keyboard.o \

LINK_LIST=\
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(ARCH_DIR)/boot.o \
$(ARCH_DIR)/descriptor_tables.o \
$(ARCH_DIR)/interrupts.o \
$(ARCH_DIR)/io.o \
$(KERNEL_DIR)/isr.o \
$(KERNEL_DIR)/serial.o \
$(KERNEL_DIR)/kmalloc.o \
$(KERNEL_DIR)/descriptor_tables.o \
$(KERNEL_DIR)/shell.o \
$(KERNEL_DIR)/timer.o \
$(KERNEL_DIR)/mmu.o \
$(ARCH_DIR)/tty.o \
$(LIBCK_OBJS) \
$(DRIVER_OBJS) \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

ISO_FILE=belux.iso
KERNEL_FILE=iso/boot/belux.bin

.PHONY: run clean all

$(KERNEL_FILE): $(ARCH_OBJS) $(LIBCK_OBJS) $(DRIVER_OBJS) $(KERNEL_OBJS)
	$(CC) -T $(ARCH_DIR)/linker.ld -o $(KERNEL_FILE) $(CFLAGS) -nostdlib $(LDFLAGS) $(LINK_LIST) $(KERNEL_DIR)/kernel.o -lgcc

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(KERNELINCLUDE)

%.o: %.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/crtbegin.o $(ARCH_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(ISO_FILE): $(KERNEL_FILE)
	grub-mkrescue -o $(ISO_FILE) iso/

run: $(ISO_FILE)
	qemu-system-i386 -serial stdio -cdrom $(ISO_FILE)

clean:
	$(RM) $(ARCH_OBJS) $(DRIVER_OBJS) $(LIBCK_OBJS) $(KERNEL_OBJS) $(KERNEL_FILE) $(ISO_FILE)

all: $(ISO_FILE)
