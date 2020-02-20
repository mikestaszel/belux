#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <kernel/tty.h>

int putchar(int ic) {
	char c = (char)ic;
	terminal_putchar(c);
	return ic;
}

void fb_put_unsigned_int(uint32_t i) {
	uint32_t n, digit;
	if (i >= 1000000000) {
		n = 1000000000;
	} else {
		n = 1;
		while (n*10 <= i) {
			n *= 10;
		}
	}
	while (n > 0) {
		digit = i / n;
		putchar('0' + digit);
		i %= n;
		n /= 10;
	}
}

void fb_put_hex(unsigned int n) {
	char* chars = "0123456789ABCDEF";
	unsigned char b = 0;
	int i;

	for (i = 7; i >= 0; --i) {
		b = (n >> i*4) & 0x0F;
		putchar(chars[b]);
	}
}

// kernel printf from aenix (http://littleosbook.github.io/):
void printf(char* s, ...) {
	va_list ap;
	char *p;
	uint32_t val;
	char *sval;

	va_start(ap, s);
	for (p = s; *p != '\0'; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		// the next character is a format character:
		switch (*++p) {
			case 'c':
				val = va_arg(ap, uint32_t);
				putchar((uint8_t) val);
				break;
			case 'u':
				val = va_arg(ap, uint32_t);
				fb_put_unsigned_int(val);
				break;
			case 'x':
				val = va_arg(ap, uint32_t);
				fb_put_hex(val);
				break;
			case 'X':
				val = va_arg(ap, uint32_t);
				fb_put_hex(val);
				break;
			case 's':
				sval = va_arg(ap, char*);
				size_t len = strlen(sval);
				for (size_t i = 0; i < len; i++) {
					putchar(sval[i]);
				}
				break;
			case '%':
				putchar('%');
				break;
		}
	}

	va_end(ap);
}
