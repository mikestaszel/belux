#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_blank();
void terminal_initialize();
void terminal_putchar(char);

#endif
