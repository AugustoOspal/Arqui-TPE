#ifndef _PONGISLIB_H_
#define _PONGISLIB_H_

#include <usrio.h>
#include <color.h>
#include <shell.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <soundLib.h>
#include <videoLib.h>
#include <soundLib.h>
#include <pongisconfig.h>
#include <pongisLevels.h>

typedef struct coordinateT
{
    uint64_t x;
    uint64_t y;
}coordinateT;

typedef coordinateT directionT;

typedef struct MipT
{
    uint8_t id; 
    uint64_t speed;
    uint32_t color;
    uint64_t radius;
    coordinateT position;
    directionT direction;
}MipT;

typedef struct BallT
{
    uint64_t speed;
    uint32_t color;
    uint64_t radius;
    coordinateT position;
}BallT;

typedef struct HoleT
{
    uint32_t color;
    uint64_t radius;
    coordinateT position;
}HoleT;

typedef MipT* MipP;
typedef BallT* BallP;
typedef HoleT* HoleP;
typedef struct LevelT
{
    MipP mip1;
    MipP mip2;
    BallP ball;
    HoleP hole;
    uint16_t level;
}LevelT;

typedef LevelT* LevelP;

void startPongisGolf();

// Helpers
void startMenu(MipT mips[]);
void endMenu(MipP winnerMip);
void drawLevel(uint16_t level, MipP mips[], BallP ball, HoleP hole);
uint8_t checkValidCirclePosition(coordinateT, uint32_t radius);

// Pelota
void drawBall(BallP ball);
void eraseBall(BallP ball);
bool canMoveBall(BallP ball);
void moveBall(BallP ball, MipP mip);

// Mip
void drawMip(MipP mip);
void walkMip(MipP mip);
bool canWalkMip(MipP mip);
void eraseMip(MipP mip);
void changeMipDir(MipP mip, uint16_t degree);
uint16_t getMipDegree(MipP mip);
void dumpMip(const MipP mip);

// Agujero
void eraseHole(HoleP hole);
void drawHole(HoleP hole);

// Colisiones
bool checkColisionMipBall(MipP mip, BallP ball);
bool checkColisionMipMip(MipP mip1, MipP mip2);
bool checkHoleCollision(BallP ball, HoleP hole);

#endif