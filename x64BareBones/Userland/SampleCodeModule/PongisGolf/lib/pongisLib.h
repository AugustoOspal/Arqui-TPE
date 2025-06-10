#ifndef _PONGISLIB_H_
#define _PONGISLIB_H_

#include <usrio.h>
#include <color.h>
#include <stdint.h>
#include <soundLib.h>
#include <videoLib.h>
#include <soundLib.h>
#include <pongisconfig.h>

/*
    TODO: EL MIP TENDRIA QUE SER UN ADT. Pero no se puede
    porque no tenemos malloc
*/

void startPongisGolf();
void drawMIP(uint64_t x, uint64_t y);

#endif