#include "stdLib.h"
#include <stdarg.h>

#define MAX_BUFF 1000
#define HEXA_MAX 16
#define BUFF_SIZE 500


// lib.asm -> De donde trabajamos con los syscalls //
extern void read(char * buffer, size_t count);
extern void write_stdin(const char * str, size_t count);
extern void get_date_time(const date_time * dt);
extern void screen_clear();
extern void change_color(uint8_t background);
extern void zoom(int in);


// TODO A IMPLEMENTAR // 
void printf(const char * str, ...);
void scanf(const char * formatt, ...);
char get_char();
char get_entry();
void put_char(const char c);
void put_str(char * s);
void put_uint(int n);
void put_int(int n);
void clear();
void zoom_in();
void zoom_out();
int str_cmp(const char* str1, const char* str2);
int str_ncmp(const char* str1, const char* str2, int n);
int str_len(const char* str);
char* str_tok(char * str1, const char* str2);
void to_lower(char * str);
void change_font_color();
void change_bg_color();
unsigned int abs(int n);