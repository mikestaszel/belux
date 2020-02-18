#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

void init_serial();
void write_serial(char c);
void write_serial_str(char* input);
char read_serial();

#endif
