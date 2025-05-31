#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawChar(char c, uint32_t hexColor, uint64_t x, uint64_t y);
void drawString(const char* str, uint32_t hexColor, uint64_t x, uint64_t y);
void drawRectangle(uint64_t width, uint64_t heigth, uint32_t hexColor, uint64_t x, uint64_t y);
void clearScreen(void);