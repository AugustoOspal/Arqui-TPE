#include <lib.h>
#include <fonts.h>
#include <stdint.h>
#include <stddef.h>
#include <videoDriver.h>

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;		// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

/*
	Nuestra parte de la implemntacion
*/

// TODO: Ninguna de estas funciones cheuqea el ancho y largo de la pantalla

uint16_t getScreenWidth()
{
    return VBE_mode_info->width;
}

uint16_t getScreenHeight()
{
    return VBE_mode_info->height;
}

void drawChar(char c, uint32_t hexColor, uint64_t x, uint64_t y)
{
    font_char_p bitmap = getCharBitMap(c);
    if (bitmap == NULL)
        return;

    for (unsigned int i = 0; i < FONT_CHAR_HEIGHT_BYTES; i++)
    {
        for (unsigned int j = 0; j < FONT_CHAR_WIDTH_BYTES; j++) // MODIFICADO: quitado '* 8'
        {
            // 0x80 = 1000 0000b
            if (bitmap[i] & (0x80 >> j))
            {
                putPixel(hexColor, x + j, y + i);
            }
        }
    }
}

static uint32_t uint64ToString(uint64_t value, char * buffer, uint32_t base)
{
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    // Handle 0 explicitly, otherwise empty string appears
    if (value == 0) {
        *p++ = '0';
        digits = 1;
    } else {
        //Calculate characters for each digit
        do
        {
            uint32_t remainder = value % base;
            *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
            digits++;
        }
        while (value /= base);
    }

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
    return digits;
}

void drawString(const char* str, uint32_t hexColor, uint64_t x, uint64_t y)
{
	unsigned int strlen = strlenght(str);
	for (unsigned int i = 0; i < strlen; i++)
	{
		drawChar(str[i], hexColor, x + (FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP) * i, y);
	}
}

void drawRectangle(uint64_t width, uint64_t heigth, uint32_t hexColor, uint64_t x, uint64_t y)
{
	for (uint64_t i = x; i < x + width; i++)
	{
		for (uint64_t j = y; j < y + heigth; j++)
		{
			putPixel(hexColor, i, j);
		}
	}
}

void drawDecimal(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y)
{
    char buffer[21]; // Max 20 digits for uint64_t in decimal + null terminator
    uint64ToString(value, buffer, 10);
    drawString(buffer, hexColor, x, y);
}

void drawHexa(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y)
{
    char buffer[19]; // "0x" + 16 hex digits for uint64_t + null terminator
    buffer[0] = '0';
    buffer[1] = 'x';
    uint64ToString(value, buffer + 2, 16);
    drawString(buffer, hexColor, x, y);
}

void drawBin(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y)
{
    char buffer[67]; // "0b" + 64 binary digits for uint64_t + null terminator
    buffer[0] = '0';
    buffer[1] = 'b';
    uint64ToString(value, buffer + 2, 2);
    drawString(buffer, hexColor, x, y);
}

/*
	TODO: Esto no se si esta bien asi o habria que borrar todo el buffer
*/

void clearScreen(void)
{
	drawRectangle(VBE_mode_info->width, VBE_mode_info->height, 0x00000000, 0, 0);
}