#include "stdLib.h"
#include <stdarg.h>
#include <stdarg.h>

#define MAX_BUFF 1000
#define HEXA_MAX 16
#define BUFF_SIZE 500


// lib.asm -> De donde trabajamos con los syscalls //
extern void read_sys(char * buffer, size_t count);
extern void write_sys(const char * str, size_t count);
extern void get_date_time_sys(const date_time * dt);
extern void screen_clear_sys();
extern void change_color_sys(uint8_t background);
extern void zoom_sys(int in);



void printf(const char * str, ...){
    va_list args;
    va_start(args, str);
    for (int i=0; str[i] != 0; i++){
        if (str[i] == '%'){
            i++;
            switch (str[i])
            {
            case 'd':
                int num = va_arg(args, int);
                put_int(num);
                break;
            case 'u':
                size_t u_num = va_arg(args, size_t);
                put_uint(u_num);    
                break;
            case 's':
                char * s = va_arg(args, char *);
                put_str(s);
                break;
            case 'c':
                char c = va_arg(args, char);
                put_char(c);
                break;
            case 'x':
                uint64_t hex = va_arg(args, uint64_t);
                put_hex(hex); 
                break;
            default:
                put_char('%');
                break;
            }
        } else if (str[i] == '\\'){
            i++;
            switch (str[i])
            {
            case 'n':
                put_char('\n');
                break;
            case 't':
                put_char('\t');
                break;
            default:
                put_char('\\');
                break;
            }
        } else {
            put_char(str[i]);
        }

    }

    va_end(args);
}

void put_char(const char c){
    write_sys(&c, 1);
}

void put_str(char * s){
    while (*s) {
        put_char(*s++);
    }
}

void put_uint(int n){
    if (n / 10) {
        put_int(n / 10);
    }
    put_char(n % 10 + '0');
}

void put_int(int n){
    if (n < 0) {
        put_char('-');
        n = -n;
    }
    put_uint(n);
}

void put_hex(uint64_t num){
    put_char('0');
    put_char('x');
    uint8_t digit = 0;
    char hexa;
    
    for(int i = HEXA_MAX-2; i >= 0; i--){
		digit = getHexDigit(num, i);
		hexa = hexa_digits[digit];
        put_char(hexa);
	}
}

uint8_t getHexDigit(uint64_t number, int position) {
    number >>= (position * 4); 
    return number & 0xF;
}

void scanf(const char * fmt, ...){
    va_list args;
    va_start(args, fmt);

    char input[BUFF_SIZE];
    fgets(input, BUFF_SIZE);
    int index = 0;

    // Aux buffer
    char buffer[BUFF_SIZE];
    void * ptr;
    int offset;

    int count = 0;
    for (int i=0; fmt[i] != 0; i++) {
        if (fmt[i] == '%') {
            switch (fmt[++i]) {
                // String
                case 's':
                    ptr = (void *) va_arg(args, char *);
                    offset = readToBlank(input, index);
                    strncpy(ptr, input + index, offset);
                    index += (offset + 1);
                    count++;
                    break;
                // Integer
                case 'd':
                    ptr = (void *) va_arg(args, int *);
                    offset = readToBlank(input, index);
                    strncpy(buffer, input + index, offset);
                    *(int *)ptr = atoi(buffer);
                    index += (offset + 1);
                    count++;
                    break;
                // Character
                case 'c':
                    if(input[index] != 0) {
                        *(char *)va_arg(args, char *) = input[index];
                        index++;
                    }
                    count++;
                    break;
                // No special format found
                default:
                    index++;
                    break;
            }
        }
    }
    va_end(args);
    return count;
}

static int readToBlank(char * str, int index) {
    int readBytes = 0;
    for(int i=index; str[i] != 0 && str[i] != '\n' && str[i] != ' ' && str[i] != '\t'; i++) {
        readBytes++;
    }
    return readBytes;
}

char * fgets(char *buffer, size_t size) {
    int readBytes = 0;
    char c;
    while(readBytes < (size-1) && (((c = getchar()) != '\n'))) {
        buffer[readBytes++] = c;
    }
    buffer[size-1] = 0;
    return buffer;
}

int atoi(const char *str) {
    int res = 0;
    for (int i = 0; str[i] != 0 && str[i] <= '9' && str[i] >= '0'; i++) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

char get_entry(){
    char buffer[1];
    buffer[0] = '\0';
    read_sys(buffer, 1);
    return buffer[0];
}

char get_char(){
    char c = get_entry();
    while(c == '\0') {
        c = get_entry();
    }
    return c;
}



void clear(){
    screen_clear_sys();
}

void zoom_in() {
    zoom_sys(1);
}

void zoom_out() {
    zoom_sys(0);
}

int str_cmp(const char* str1, const char* str2){
    while(*str1 != '\0' && *str2 != '\0') {
        if(*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    if(*str1 == '\0' || *str2 == '\0')
        return *str1 - *str2;
}

int str_ncmp(const char* str1, const char* str2, int n){
    int i = 0;
    while(*str1 != '\0' && *str2 != '\0' && i < n) {
        if(*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    if(*str1 == '\0' || *str2 == '\0')
        return *str1 - *str2;
}

void strcpy(char *dest, const char *src) {
    size_t i = 0;
    while(src[i] != 0) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    while(src[i] != 0 && i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
}

int str_len(const char* str){
    size_t len = 0;
    while(str[len] != 0) {
        len++;
    }
    return len;
}

void to_lower(char * str){
    for (int i=0; str[i] != 0; i++){
        if ('A' <= str[i] && str[i] <= 'Z'){
            str[i] += ('a'-'A');
        }
    }
}

void change_font_color(){
    change_color(0);
}

void change_bg_color(){
    change_color(1);
}

unsigned int abs(int n){
    return n < 0 ? -n : n;
}