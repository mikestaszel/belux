#ifndef _KERNEL_IO_PORTS_H
#define _KERNEL_IO_PORTS_H

extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

#endif
