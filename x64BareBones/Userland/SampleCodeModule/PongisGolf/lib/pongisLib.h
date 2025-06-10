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
    Estaria bueno hacer un ADT pero no podemos porque
    no tenemos malloc
*/

typedef struct MipT
{
    uint64_t x;
    uint64_t y;
    uint64_t speed;
    uint64_t radius;
    uint32_t color;
    int16_t degree; // 0 arriba, 1 derecha, 2 abajo, 3 izquierda  
}MipT;

typedef struct BallT
{
    uint64_t x;
    uint64_t y;
    uint64_t speed;
    uint64_t radius;
    uint32_t color;
}BallT;

typedef struct HoleT
{
    uint64_t x;
    uint64_t y;
    uint64_t radius;
    uint32_t color;
}HoleT;

typedef MipT* MipP;
typedef BallT* BallP;
typedef HoleT* HoleP;

// Helpers
void drawLevel(MipP mip1, MipP mip2, BallP ball, HoleP hole);
uint8_t checkColisionMipBall(MipP mip, BallP ball);
uint8_t checkValidScreenPosition(uint32_t x, uint32_t y, uint32_t radius);

// Pelota
void drawBall(BallP ball);
void eraseBall(BallP ball);
void moveBall(BallP ball, MipP mip);

// Mip
void startPongisGolf();
void drawMip(MipP mip);
void walkMip(MipP mip);
void eraseMip(MipP mip);
void changeMipDir(MipP mip, uint16_t degree);
uint16_t getMipDegree(MipP mip);

// Agujero
void eraseHole(HoleP hole);
void drawHole(HoleP hole);
uint8_t checkHoleCollision(BallP ball, HoleP hole);

#endif