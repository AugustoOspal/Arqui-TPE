#ifndef _KEYBOARDDRIVER_H
#define _KEYBOARDDRIVER_H

#include <lib.h>
#include <stddef.h>

typedef enum {
    LEFT = 1,
    UP,
    DOWN, 
    RIGHT
} ARROWS;

void press_key();
unsigned char get_key();
extern uint8_t esc;
void load_buffer(char * buffer, size_t count);

#endif 