#include <soundLib.h>

void playSound(uint32_t frequency, uint32_t duration) {
    sys_playSound(frequency, duration);
}