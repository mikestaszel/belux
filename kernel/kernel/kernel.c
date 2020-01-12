#include <stdio.h>
#include <kernel/tty.h>

void kernel_main() {
	terminal_initialize();
	
	printf("Hello, world!\n");
	printf("A second line!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nLAST LINE!\n");
	printf("OH NO!\n");
	printf("AND ANOTHER ONE!\nA really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really really long line?\nHi there!\nHi there!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nHi!\nWOAH!\n");
	printf("Scrolling!\n");
}
