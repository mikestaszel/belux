#include <stddef.h>
#include <stdio.h>
#include <string.h>

int printf(const char* str) {
	// very very very simple and bad printf
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++) {
		putchar(str[i]);
	}
	return 0;
}
