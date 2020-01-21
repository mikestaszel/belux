CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=
NASMFLAGS?=

CC:=i686-elf-gcc
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
NASMFLAGS:=-felf32 -w+orphan-labels

ARCH_DIR:=kernel/arch/i386
LIBCK_DIR:=kernel/libck
KERNEL_DIR:=kernel/kernel

ARCH_OBJS=\
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(ARCH_DIR)/boot.o \
$(ARCH_DIR)/idt.o \
$(ARCH_DIR)/io_ports.o \
$(ARCH_DIR)/tty.o \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

LIBCK_OBJS=\
$(LIBCK_DIR)/stdio/printf.o \
$(LIBCK_DIR)/stdio/putchar.o \
$(LIBCK_DIR)/string/memset.o \
$(LIBCK_DIR)/string/strlen.o \

KERNEL_OBJS=\
$(KERNEL_DIR)/idt_init.o \
$(KERNEL_DIR)/irq.o \
$(KERNEL_DIR)/kernel.o \

LINK_LIST=\
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(ARCH_DIR)/boot.o \
$(ARCH_DIR)/idt.o \
$(ARCH_DIR)/io_ports.o \
$(KERNEL_DIR)/idt_init.o \
$(KERNEL_DIR)/irq.o \
$(ARCH_DIR)/tty.o \
$(LIBCK_OBJS) \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

ISO_FILE=belux.iso
KERNEL_FILE=iso/boot/belux.bin

.PHONY: run clean all

$(KERNEL_FILE): $(ARCH_OBJS) $(LIBCK_OBJS) $(KERNEL_OBJS)
	$(CC) -T $(ARCH_DIR)/linker.ld -o $(KERNEL_FILE) $(CFLAGS) -nostdlib $(LDFLAGS) $(LINK_LIST) $(KERNEL_DIR)/kernel.o -lgcc

$(KERNEL_DIR)/idt_init.o: $(KERNEL_DIR)/idt_init.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/include -Ikernel/libck/include

$(KERNEL_DIR)/irq.o: $(KERNEL_DIR)/irq.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/include -Ikernel/libck/include

$(KERNEL_DIR)/kernel.o: $(KERNEL_DIR)/kernel.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/include -Ikernel/libck/include

$(ARCH_DIR)/boot.o: $(ARCH_DIR)/boot.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/crti.o: $(ARCH_DIR)/crti.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/crtn.o: $(ARCH_DIR)/crtn.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/crtbegin.o $(ARCH_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(ARCH_DIR)/idt.o: $(ARCH_DIR)/idt.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/io_ports.o: $(ARCH_DIR)/io_ports.asm
	nasm $(NASMFLAGS) $< -o $@

$(ARCH_DIR)/tty.o: $(ARCH_DIR)/tty.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/include -Ikernel/libck/include

$(LIBCK_DIR)/stdio/printf.o: $(LIBCK_DIR)/stdio/printf.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/libck/include

$(LIBCK_DIR)/stdio/putchar.o: $(LIBCK_DIR)/stdio/putchar.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/include -Ikernel/libck/include

$(LIBCK_DIR)/string/memset.o: $(LIBCK_DIR)/string/memset.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/libck/include

$(LIBCK_DIR)/string/strlen.o: $(LIBCK_DIR)/string/strlen.c
	$(CC) -c $< -o $@ $(CFLAGS) -std=gnu11 -Ikernel/libck/include

$(ISO_FILE): $(KERNEL_FILE)
	grub-mkrescue -o $(ISO_FILE) iso/

run: $(ISO_FILE)
	qemu-system-i386 -cdrom $(ISO_FILE)

clean:
	$(RM) $(ARCH_OBJS) $(LIBCK_OBJS) $(KERNEL_OBJS)
	$(RM) $(KERNEL_FILE) $(ISO_FILE)

all: $(ISO_FILE)
