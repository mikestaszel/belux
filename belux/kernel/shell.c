#include <stdio.h>
#include <string.h>
#include <kernel/kmalloc.h>
#include <drivers/keyboard.h>
#include <kernel/io.h>
#include <kernel/serial.h>
#include <kernel/tty.h>
#include <kernel/shell.h>

#define MAX(a, b) \
   ({ __typeof__ (a) _a = (a); \
	   __typeof__ (b) _b = (b); \
	 _a > _b ? _a : _b; })

#define MIN(a, b) \
   ({ __typeof__ (a) _a = (a); \
	   __typeof__ (b) _b = (b); \
	 _a < _b ? _a : _b; })

#define KEY_BUFFER_INITIAL_SIZE 0x100
static char* key_buffer;
static size_t key_buffer_size;
static size_t key_buffer_used;
static size_t key_buffer_printed;

int strncmp(const char* str1, const char* str2, size_t num) {
	while (*str1 && num && (*str1 == *str2)) {
		++str1;
		++str2;
		--num;
	}
	return num == 0 ? 0 : *(unsigned char*) str1 - *(unsigned char*) str2;
}

char* strncpy(char* restrict s1, const char* restrict s2, size_t n) {
	char* rc = s1;
	while ((n > 0) && (*s1++ = *s2++)) --n;
	while (n-- > 1) *s1++ = '\0';
	return rc;
}

void key_buffer_print() {
	if (key_buffer_printed < key_buffer_used) {
		write_serial_str(key_buffer + key_buffer_printed);
		key_buffer_printed = key_buffer_used;
	}
	while (key_buffer_printed > key_buffer_used) {
		printf("\b \b");
		key_buffer_printed--;
	}
}

static void print_prompt(int ret) {
	printf("%d # ", ret);
}

static void shell_callback(char* input) {
	int ret = 1;
	int save = 0;
	if (strncmp(input, "exit", 4) == 0 || strncmp(input, "poweroff", 8) == 0) {
		// outb(0xf4, 0x00);
		// outb(0xB004, 0x2000);
		// outb(0x604, 0x2000);
		ret = 0;
	} else if (strncmp(input, "echo ", 5) == 0) {
		printf("%s\n", input + 5);
		ret = 0;
	} else {
		printf("Command not found: %s\n", input);
		save = 0;
	}
	print_prompt(ret);
}

void shell_init() {
	print_prompt(0);
}

void shell_read() {
	char c = read_serial();
	if (c == '\r' || c == '\n') {
		key_buffer_return();
	} else if (c == '\b' || c == 0x7F /* DEL */) {
		key_buffer_backspace();
	} else {
		key_buffer_append(c);
	}
}

char key_buffer_append(const char c) {
	if (key_buffer == NULL) {
		key_buffer = kmalloc(key_buffer_size = KEY_BUFFER_INITIAL_SIZE);
		if (key_buffer == NULL) return 0;
	} else if (key_buffer_size <= key_buffer_used + 1) {
		key_buffer = krealloc(key_buffer, key_buffer_size += KEY_BUFFER_INITIAL_SIZE);
		if (key_buffer == NULL) return 0;
	}

	terminal_putchar(c);

	key_buffer[key_buffer_used++] = c;
	key_buffer[key_buffer_used] = '\0';
	
	return 1;
}

void key_buffer_backspace() {
	if (key_buffer_used > 0) {
		key_buffer[--key_buffer_used] = '\0';
		handle_backspace();
	}
}

void key_buffer_clear() {
	key_buffer[key_buffer_used = 0] = '\0';
	key_buffer_printed = 0;

	if (key_buffer_size > KEY_BUFFER_INITIAL_SIZE) {
		key_buffer = krealloc(key_buffer, key_buffer_size = KEY_BUFFER_INITIAL_SIZE);
	}
}

void key_buffer_set(char *input) {
	while (key_buffer_used--) {
		printf("\b \b");
	}
	key_buffer_used = strlen(input);
	key_buffer = krealloc(key_buffer, MAX(key_buffer_used + 1, KEY_BUFFER_INITIAL_SIZE));
	if (key_buffer == NULL) return;
	strncpy(key_buffer, input, key_buffer_used + 1);
	key_buffer_printed = 0;
	key_buffer_print();
}

void key_buffer_return() {
	terminal_putchar('\n');
	shell_callback(key_buffer);
	key_buffer_clear();
}
