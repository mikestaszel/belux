#include <stddef.h>

#include <kernel/tty.h>

void kernel_main() {
	terminal_initialize();
	terminal_writestring("Hello, world!\n");
	terminal_writestring("A second line!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nLAST LINE!\n");
	terminal_writestring("OH NO!\n");
	terminal_writestring("AND ANOTHER ONE!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nWOAH!\n");
	terminal_writestring("Scrolling!\n");
}
