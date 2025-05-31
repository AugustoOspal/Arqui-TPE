#ifndef _FONTS_H_
#define _FONTS_H_

#include <stdint.h>


// Todo: Ver si alguna de estas constantes ya esta en pure64 definida y usarla de ahi

// Dimensiones de las fuentes
#define FONT_CHAR_HEIGHT_BYTES 16
#define FONT_CHAR_WITH_BYTES 1

// Cantidad de pixeles de espacio entre chars (Horizontal)
#define FONT_CHAR_GAP 1

#define FIRST_PRINTABLE_CHAR 0x20
#define LAST_PRINTABLE_CHAR 0x7E
#define QNTY_PRINTABLE_CHARS (LAST_PRINTABLE_CHAR - FIRST_PRINTABLE_CHAR + 1)

typedef const uint8_t font_char_t[FONT_CHAR_HEIGHT_BYTES];
typedef const uint8_t* font_char_p;

font_char_p getCharBitMap(char c);

#endif