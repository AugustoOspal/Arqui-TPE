#ifndef _SYSCALL_LIB_H
#define _SYSCALL_LIB_H

#include <stdint.h>

// Video
extern void sys_clearScreen(void);
extern void sys_putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
extern void sys_drawChar(char c, uint32_t hexColor, uint64_t x, uint64_t y);
extern void sys_drawString(const char *str, uint32_t hexColor, uint64_t x, uint64_t y);
extern void sys_drawRectangle(uint64_t width, uint64_t height, uint32_t hexColor, uint64_t x, uint64_t y);
extern void sys_drawDecimal(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y);
extern void sys_drawHexa(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y);
extern void sys_drawBin(uint64_t value, uint32_t hexColor, uint64_t x, uint64_t y);
extern uint16_t sys_detScreenWidth(void);
extern uint16_t sys_detScreenHeight(void);

// Teclado
extern char sys_kbdGetChar(void);

#endif