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

// Teclado. Esta a lo mejor la tendriamos que sacar porque tenemos sys_read ya
extern char sys_kbdGetChar(void);


// Shell
extern uint64_t sys_write(uint8_t fd, const char *str, uint64_t count);
extern uint64_t sys_read(uint8_t fd, char *buffer, uint64_t count);

#endif