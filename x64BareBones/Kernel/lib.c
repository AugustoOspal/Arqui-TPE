#include <stdint.h>

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

unsigned int strlenght(const char* str)
{
	unsigned int counter;
	for (counter = 0; str[counter];counter++);
	return counter;
}

// Convierte value a cadena en base “base” (2,10,16…) y la escribe en buffer (debe tener espacio suficiente).
// Devuelve buffer.
char* uint64ToString(uint64_t value, char *buffer, int base) {
    char *p = buffer, *p1, tmp;
    uint64_t v = value;
    if (v == 0) {
        *p++ = '0';
        *p   = '\0';
        return buffer;
    }
    // Generar dígitos en orden inverso
    while (v) {
        int digit = v % base;
        *p++ = digit < 10 ? '0' + digit : 'a' + (digit - 10);
        v /= base;
    }
    *p-- = '\0';
    // Invertir la cadena
    p1 = buffer;
    while (p1 < p) {
        tmp  = *p;
        *p-- = *p1;
        *p1++ = tmp;
    }
    return buffer;
}