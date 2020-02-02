#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

void fb_put_ui(uint32_t i)
{
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
		putchar('0'+digit);
		i %= n;
		n /= 10;
	}
}

void fb_put_ui_hex(unsigned int n)
{
	char *chars = "0123456789ABCDEF";
	unsigned char b = 0;
	int i;

	putchar('0');
	putchar('x');

	for (i = 7; i >= 0; --i) {
		b = (n >> i*4) & 0x0F;
		putchar(chars[b]);
	}
}

void fb_put_s(const char* str) {
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++) {
		putchar(str[i]);
	}
}

void printf(char *s, ...)
{
	va_list ap;
	char *p;
	uint32_t uival;
	char *sval;

	va_start(ap, s);
	for (p = s; *p != '\0'; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		switch (*++p) {
			case 'c':
				uival = va_arg(ap, uint32_t);
				putchar((uint8_t) uival);
				break;
			case 'u':
				uival = va_arg(ap, uint32_t);
				fb_put_ui(uival);
				break;
			case 'x':
				uival = va_arg(ap, uint32_t);
				fb_put_ui_hex(uival);
				break;
			case 'X':
				uival = va_arg(ap, uint32_t);
				fb_put_ui_hex(uival);
				break;
			case 's':
				sval = va_arg(ap, char*);
				fb_put_s(sval);
				break;
			case '%':
				putchar('%');
				break;
		}
	}

	va_end(ap);
}
