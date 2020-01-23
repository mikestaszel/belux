CFLAGS?=-O2 -g -std=gnu11
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
$(ARCH_DIR)/gdt.o \
$(ARCH_DIR)/idt.o \
$(ARCH_DIR)/tss.o \
$(ARCH_DIR)/io_ports.o \
$(ARCH_DIR)/tty.o \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

LIBCK_OBJS=\
$(LIBCK_DIR)/stdio/printf.o \
$(LIBCK_DIR)/stdio/putchar.o \
$(LIBCK_DIR)/string/memcmp.o \
$(LIBCK_DIR)/string/memcpy.o \
$(LIBCK_DIR)/string/memmove.o \
$(LIBCK_DIR)/string/memset.o \
$(LIBCK_DIR)/string/strlen.o \

KERNEL_OBJS=\
$(KERNEL_DIR)/idt.o \
$(KERNEL_DIR)/irq.o \
$(KERNEL_DIR)/gdt.o \
$(KERNEL_DIR)/tss.o \
$(KERNEL_DIR)/kernel.o \

DRIVERS_OBJS=\
$(DRIVERS_DIR)/keyboard.o \

LINK_LIST=\
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(ARCH_DIR)/boot.o \
$(ARCH_DIR)/gdt.o \
$(ARCH_DIR)/idt.o \
$(ARCH_DIR)/tss.o \
$(ARCH_DIR)/io_ports.o \
$(KERNEL_DIR)/idt.o \
$(KERNEL_DIR)/irq.o \
$(KERNEL_DIR)/tss.o \
$(KERNEL_DIR)/gdt.o \
$(ARCH_DIR)/tty.o \
$(LIBCK_OBJS) \
$(DRIVERS_OBJS) \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

ISO_FILE=belux.iso
KERNEL_FILE=iso/boot/belux.bin

.PHONY: run iso clean all

$(KERNEL_FILE): $(ARCH_OBJS) $(LIBCK_OBJS) $(DRIVERS_OBJS) $(KERNEL_OBJS)
	$(CC) -T $(ARCH_DIR)/linker.ld -o $(KERNEL_FILE) $(CFLAGS) -nostdlib $(LDFLAGS) $(LINK_LIST) $(KERNEL_DIR)/kernel.o -lgcc

$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(KERNELINCLUDE)

$(DRIVERS_DIR)/%.o: $(DRIVERS_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(KERNELINCLUDE)

$(ARCH_DIR)/%.o: $(ARCH_DIR)/%.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/crtbegin.o $(ARCH_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(ARCH_DIR)/%.o: $(ARCH_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(KERNELINCLUDE)

$(LIBCK_DIR)/stdio/%.o: $(LIBCK_DIR)/stdio/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(KERNELINCLUDE)

$(LIBCK_DIR)/string/%.o: $(LIBCK_DIR)/string/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(KERNELINCLUDE)

$(ISO_FILE): $(KERNEL_FILE)
	grub-mkrescue -o $(ISO_FILE) iso/

iso: $(ISO_FILE)

run: $(ISO_FILE)
	qemu-system-i386 -cdrom $(ISO_FILE)

clean:
	$(RM) $(ARCH_OBJS) $(LIBCK_OBJS) $(KERNEL_OBJS) $(KERNEL_FILE) $(ISO_FILE)

all: $(ISO_FILE)
