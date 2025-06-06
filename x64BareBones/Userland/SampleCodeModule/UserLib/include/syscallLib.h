#ifndef _SYSCALL_LIB_H
#define _SYSCALL_LIB_H

#include <stdint.h>

extern void sys_DrawString(const char *str, uint32_t hexColor, uint64_t x, uint64_t y);

#endif