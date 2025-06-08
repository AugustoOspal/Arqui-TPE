#include <soundDriver.h>

// Codigo de https://wiki.osdev.org/PC_Speaker

//Play sound using built-in speaker
static void play_sound(uint32_t nFrequence) {
    uint32_t Div;
    uint8_t tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t) (Div) );
    outb(0x42, (uint8_t) (Div >> 8));

    //And play the sound using the PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}
 
//make it shut up
static void nosound() {
    uint8_t tmp = inb(0x61) & 0xFC;
        
    outb(0x61, tmp);
}
 
//Make a beep
void beep() {
    play_sound(1000);
    timer_wait(10);
    nosound();
    //set_PIT_2(old_frequency);
}

// Corto y agudo
void game_blip_sound() {
    play_sound(2500);
    timer_wait(3);
    nosound();
}

// Corto y grave
void game_thud_sound() {
    play_sound(500);
    timer_wait(4);
    nosound();
}

void play_boot_sound() {
    play_sound(300);
    timer_wait(15);
    timer_wait(2);

    play_sound(600);
    timer_wait(10);
    timer_wait(2);

    play_sound(900);
    timer_wait(20);
    nosound();
}