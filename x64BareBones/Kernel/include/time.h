#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();

typedef struct{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;
}dateTime;

// Tiempo RTC
unsigned int getSysSeconds(void);
unsigned int getSysMinutes(void);
unsigned int getSysHours(void);
unsigned int getSysDayOfWeek(void);
unsigned int getSysDayOfMonth(void);
unsigned int getSysMonth(void);
unsigned int getSysYear(void);

#endif
