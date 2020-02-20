#ifndef _KERNEL_SHELL_H
#define _KERNEL_SHELL_H

void key_buffer_clear();
char key_buffer_append(char c);
void key_buffer_backspace();
void key_buffer_return();
void key_buffer_print();
void print_prompt(int ret);
void shell_init();

#endif
