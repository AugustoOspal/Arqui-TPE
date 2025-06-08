#ifndef _SOUND_DRIVER_H_
#define _SOUND_DRIVER_H_

#include <stdint.h>

extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);

void beep();
void game_blip_sound();
void game_thud_sound();
void play_boot_sound();

#endif