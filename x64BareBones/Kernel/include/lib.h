#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

// Tiempo RTC
unsigned int getSysSeconds(void);
unsigned int getSysMinutes(void);
unsigned int getSysHours(void);
unsigned int getSysDayOfWeek(void);
unsigned int getSysDayOfMonth(void);
unsigned int getSysMonth(void);
unsigned int getSysYear(void);

unsigned int strlenght(const char* str);

#endif