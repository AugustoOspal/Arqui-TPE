#include <pongisLib.h>

// TODO: Esto despues creo que tendriamos que hacer una funcion
#define ARRAY_LEN(a)  (sizeof(a) / sizeof((a)[0]))

// TODO: Poner enums
char *colorsS[] = {"White", "Orange", "Pink", "Peach"};
uint32_t colors[] = {WHITE, ORANGE, PINK, PEACH};


// Helpers

uint8_t checkValidScreenPosition(coordinateT position, uint32_t radius)
{
    uint64_t x = position.x;
    uint64_t y = position.y;

    uint32_t screenWidth = getScreenWidth();
    uint32_t screenHeight = getScreenHeight();

    return (x + radius < screenWidth && x >= radius && y + radius < screenHeight && y >= radius);
}

/*
    TODO: Cosas para mejorar de startMenu:

    -   Cuando el usuario ingresa la cantidad de jugadores o el color
        se deberia mostrar en pantalla lo que el jugador esta seleccionando
        mientras lo selecciona, y que termine de seleccionarlo cuando presione
        enter.
*/
void startMenu(MipT mips[])
{
    clearScreen();
    puts("Bienvenidos a Pongis Golf!");
    playStartMusic();

    // Seleccion de cantidad de jugadores
    // unsigned int playersCounter = 0;
    // printf("Seleccione la cantidad de jugadores: ");
    

    unsigned int colorsCount = ARRAY_LEN(colors);
    for (unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        printf("Seleccione el color del mip numero %d:", i + 1);
        for (unsigned int j = 0; j < colorsCount; j++)
        {
            printf("\n%d: %s", j + 1, colorsS[j]);
        }

        char c;
        do
        {
            c = getchar() - '0';
        } while (!c || c > colorsCount);
        
        c--;
        mips[i].color = colors[c];
        clearScreen();
        printf("Color seleccionado: %s", colorsS[c]);
        sleepMilli(2000);
        clearScreen();
    }
}

// Seccion Mip
void drawMip(MipP mip)
{
    // Dibujar cuerpo
    drawCircle(mip->radius, mip->color, mip->position.x, mip->position.y);

    uint64_t eye_radius = (mip->radius * MIP_EYE_RADIUS) / 100;
    uint64_t eye_distance = mip->radius / 2;  // Distancia del centro al ojo

}

void eraseMip(MipP mip)
{
    drawCircle(mip->radius, BACKGROUND_COLOR, mip->position.x, mip->position.y);
}

void dumpMip(const MipP mip)
{
    if (mip == NULL) {
        printf("Mip is NULL\n");
        return;
    }

    printf("Mip ID: %d\n", mip->id);
    printf("Position: (%u, %u)\n", mip->position.x, mip->position.y);
    printf("Direction: (%u, %u)\n", mip->direction.x, mip->direction.y);
    printf("Radius: %u\n", mip->radius);
    printf("Speed: %u\n", mip->speed);
    printf("Color: %u\n", mip->color);
}