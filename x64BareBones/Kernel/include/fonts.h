#ifndef _FONTS_H_
#define _FONTS_H_

#include <stdint.h>

#define FONTS 3

extern int currentFont;

// Todo: Ver si alguna de estas constantes ya esta en pure64 definida y usarla de ahi

// Dimensiones de las fuentes
#define FONT_CHAR_HEIGHT_BYTES 16
#define FONT_CHAR_HEIGHT_MEDIUM_BYTES 32
#define FONT_CHAR_HEIGHT_LARGE_BYTES 48

#define FONT_CHAR_WIDTH_BYTES 8
#define FONT_CHAR_WIDTH_MEDIUM_BYTES 16
#define FONT_CHAR_WIDTH_LARGE_BYTES 24

// Font pequeña (8 bits)
#define FONT_MASK_SMALL  0x80        // 1000 0000b

// Font mediana (16 bits)
#define FONT_MASK_MEDIUM 0x8000      // 1000 0000 0000 0000b

// Font grande (24 bits)
#define FONT_MASK_LARGE  0x800000    // 1000 0000 0000 0000 0000 0000b

// Cantidad de pixeles de espacio entre chars (Horizontal)
#define FONT_CHAR_GAP 1

#define FIRST_PRINTABLE_CHAR 0x20
#define LAST_PRINTABLE_CHAR 0x7E
#define QNTY_PRINTABLE_CHARS (LAST_PRINTABLE_CHAR - FIRST_PRINTABLE_CHAR + 1)

// Font pequeña: 8x16 (1 byte por fila)
typedef const uint8_t font_char_t[FONT_CHAR_HEIGHT_BYTES];

// Font mediana: 16x32 (2 bytes por fila)
typedef const uint16_t font_char_medium_t[FONT_CHAR_HEIGHT_MEDIUM_BYTES ];

// Font grande: 24x48 (3 bytes por fila, pero usamos uint32_t para alinear)
typedef const uint32_t font_char_large_t[FONT_CHAR_HEIGHT_LARGE_BYTES];

typedef const void* font_char_p;
typedef const void* const* font_char_map;

typedef struct {
    font_char_p bitmap;  // puntero al bitmap (uint8_t*, uint16_t*, etc.)
    int height;          // cantidad de filas (ej: 16, 32, 48)
    int width;           // cantidad de columnas (ej: 8)
    uint32_t bitMask; // máscara para recorrer los bits en una fila
} FontChar;

FontChar getCharBitMap(char c);

int getWidth();
int getHeight();

extern int currentFont;
void zoomIn();
void zoomOut();



#endif