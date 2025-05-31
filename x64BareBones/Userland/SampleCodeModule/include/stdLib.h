#ifndef _STDLIBRARY_H_
#define _STDLIBRARY_H_
#include <stddef.h>
#include <stdint.h>


typedef struct{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;
}date_time;

static char hexa_digits[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void printf(const char * str, ...);
void scanf(const char * formatt, ...);
char * fgets(char *buffer, size_t size);
char get_char();
char get_entry();
void put_char(const char c);
void put_str(char * s);
void put_uint(int n);
void put_int(int n);
void put_hex(uint64_t num);
int atoi(const char *str);
void clear();   
void zoom_in();
void zoom_out();
int str_cmp(const char* str1, const char* str2);
int str_ncmp(const char* str1, const char* str2, int n);
void strcpy(char *dest, const char *src);
void strncpy(char *dest, const char *src, size_t n);
int str_len(const char* str);
void to_lower(char * str);
void change_font_color();
void change_bg_color();
unsigned int abs(int a);
#endif