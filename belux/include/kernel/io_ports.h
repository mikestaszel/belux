#ifndef _KERNEL_IO_PORTS_H
#define _KERNEL_IO_PORTS_H

extern char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char data);

#endif
