#ifndef _USRIO_H_
#define _USRIO_H_

#include <stdarg.h>
#include <syscallLib.h>

int scanf(const char *format, ...);
int printf(const char *format, ...);
int putchar(char c);
char getchar(void);
int puts(const char *s);

#endif