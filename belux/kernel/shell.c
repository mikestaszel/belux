#include <stdio.h>
#include <string.h>
#include <kernel/kmalloc.h>
#include <drivers/keyboard.h>
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
	printf("%u # ", ret);
}

static void shell_callback(char* input) {
	int ret = 1;
	int save = 0;
	if (strncmp(input, "ls", 2) == 0) {
		printf("no ls for you.\n");
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

void key_buffer_set(char* input) {
	while (key_buffer_used--) {
		printf("\b \b");
	}
	key_buffer_used = strlen(input);
	key_buffer = krealloc(key_buffer, MAX(key_buffer_used + 1, KEY_BUFFER_INITIAL_SIZE));
	if (key_buffer == NULL) {
		return;
	}
	strncpy(key_buffer, input, key_buffer_used + 1);
	key_buffer_printed = 0;
	key_buffer_print();
}

void key_buffer_return() {
	terminal_putchar('\n');
	shell_callback(key_buffer);
	key_buffer_clear();
}
