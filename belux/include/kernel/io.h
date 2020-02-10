#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
short inw(unsigned short port);

#endif
