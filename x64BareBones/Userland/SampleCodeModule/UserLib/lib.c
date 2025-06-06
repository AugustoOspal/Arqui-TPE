#include <lib.h>

void drawString(const char* str, uint32_t hexColor, uint64_t x, uint64_t y) {
    sys_DrawString(str, hexColor, x, y);
}