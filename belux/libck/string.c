#include <stddef.h>
#include <string.h>

int memcmp(const void* str1, const void* str2, size_t count) {
	const unsigned char* s1 = str1;
	const unsigned char* s2 = str2;

	while (count-- > 0) {
		if (*s1++ != *s2++) {
			if (s1[-1] < s2[-1]) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

void* memcpy(void* dest, const void* src, size_t len) {
	char* d = dest;
	const char* s = src;

	while (len-- > 0) {
		*d++ = *s++;
	}

	return dest;
}

void* memmove(void* dest, void* src, size_t len) {
	char* d = dest;
	char* s = src;

	if (d < s) {
		while (len--) {
			*d++ = *s++;
		}
	}
	else {
		char* lasts = s + (len - 1);
		char* lastd = d + (len - 1);

		while (len--) {
			*lastd-- = *lasts--;
		}
	}
	return dest;
}

void* memset(void* dest, int val, size_t len) {
	unsigned char* ptr = dest;
	while (len-- > 0) {
		*ptr++ = val;
	}
	return dest;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len]) {
		len++;
	}
	return len;
}

int strcmp(const char* const str1, const char* const str2) {
	const unsigned char* p1 = (unsigned char*) str1;
	const unsigned char* p2 = (unsigned char*) str2;

	while (*p1 != '\0' && *p1 == *p2) {
		p1++, p2++;
	}

	return *p1 - *p2;
}

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
	while ((n > 0) && (*s1++ = *s2++)) {
		--n;
	}
	while (n-- > 1) {
		*s1++ = '\0';
	}
	return rc;
}
