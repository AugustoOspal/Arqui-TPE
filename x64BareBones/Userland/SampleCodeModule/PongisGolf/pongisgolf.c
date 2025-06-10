#include <color.h>
#include <pongisLib.h>
#include <pongisconfig.h>

static uint64_t mipX = 100;
static uint64_t mipY = 100;

void startPongisGolf() 
{
    clearScreen();
    paintScreen(BACKGROUND_COLOR);
    drawMIP(mipX, mipY);


    /*
        Toda esta parte es tester para ver mas o menos como deberia ser
    */
    char c;
    while (1)
    {
        c = getchar();
        if (c == 'd')
        {
            drawCircle(MIP_RADIUS, BACKGROUND_COLOR, mipX, mipY); // Limpiar el MIP
            mipX += MIP_INITIAL_SPEED;
            drawMIP(mipX, mipY);
        }
    }
    

    return 0;
}