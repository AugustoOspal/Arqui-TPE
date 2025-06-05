#ifndef _VIDEODRIVER_H_
#define _VIDEODRIVER_H_

#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawChar(char c, uint32_t hexColor, uint64_t x, uint64_t y);
void drawString(const char* str, uint32_t hexColor, uint64_t x, uint64_t y);
void drawRectangle(uint64_t width, uint64_t heigth, uint32_t hexColor, uint64_t x, uint64_t y);
void clearScreen(void);

// Funciones para dibujar números
void drawDecimal(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y);
void drawHexa(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y); // Ya estaba declarada
void drawBin(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y);

#endif // _VIDEODRIVER_H_ // Asegúrate que el guard sea correcto si no es este