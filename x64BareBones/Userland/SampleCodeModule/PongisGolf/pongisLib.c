#include <pongisLib.h>

static uint8_t playersCounter = 0;

// Helpers
void drawLevel(MipP mip1, MipP mip2, BallP ball, HoleP hole)
{
    paintScreen(BACKGROUND_COLOR);
}

uint8_t checkColisionMipBall(const MipP mip, const BallP ball)
{
    // Calcular la distancia entre los centros de ambos círculos
    int64_t dx = (int64_t)mip->x - (int64_t)ball->x;
    int64_t dy = (int64_t)mip->y - (int64_t)ball->y;
    
    // Pitagoras
    uint64_t distanceSquared = (dx * dx) + (dy * dy);
    
    // Calcular la suma de los radios
    uint64_t radiiSum = mip->radius + ball->radius;
    
    // Calcular la suma de radios al cuadrado
    uint64_t radiiSumSquared = radiiSum * radiiSum;
    
    // Si la distancia al cuadrado es menor o igual que la suma de radios al cuadrado,
    // entonces hay colisión
    return distanceSquared <= radiiSumSquared;
}

uint8_t checkValidScreenPosition(uint32_t x, uint32_t y, uint32_t radius)
{
    uint32_t screenWidth = getScreenWidth();
    uint32_t screenHeight = getScreenHeight();

    return (x + radius >= screenWidth || x <= radius || y + radius >= screenHeight || y <= radius);
}


// Seccion Mip
void drawMip(MipP mip)
{
    // Dibujar cuerpo
    drawCircle(mip->radius, mip->color, mip->x, mip->y);

    uint64_t eye_radius = (mip->radius * MIP_EYE_RADIUS) / 100;
    uint64_t eye_distance = mip->radius / 2;  // Distancia del centro al ojo
    
    // Posición del ojo según la dirección
    int64_t eye_x, eye_y;
    
    switch(mip->degree) {
        case 0: // Arriba
            eye_x = mip->x;
            eye_y = mip->y - eye_distance;
            break;
            
        case 1: // Derecha
            eye_x = mip->x + eye_distance;
            eye_y = mip->y;
            break;
            
        case 2: // Abajo
            eye_x = mip->x;
            eye_y = mip->y + eye_distance;
            break;
            
        case 3: // Izquierda
            eye_x = mip->x - eye_distance;
            eye_y = mip->y;
            break;
            
        default: // Por defecto, mirando arriba
            eye_x = mip->x;
            eye_y = mip->y - eye_distance;
            break;
    }
    
    // Dibujar el ojo
    drawCircle(eye_radius, MIP_EYE_COLOR, eye_x, eye_y);
}

void eraseMip(MipP mip)
{
    drawCircle(mip->radius, BACKGROUND_COLOR, mip->x, mip->y);
}

void changeMipDir(MipP mip, uint16_t degree)
{
    mip->degree = degree;
    drawMip(mip);
}

void walkMip(MipP mip)
{
    /*
        TODO: Cambiar la forma en que lo borra para
        no repetir codigo. Tiene que ser antes
        de que actualice la posicion
    */

    switch(mip->degree) {
        case 0: // Arriba
            eraseMip(mip);
            if (!checkValidScreenPosition(mip->x, mip->y - mip->speed, mip->radius)) {
                break;
            }
            mip->y -= mip->speed;
            break;
        case 1: // Derecha
            eraseMip(mip);
            mip->x += mip->speed;
            break;
        case 2: // Abajo
            eraseMip(mip);
            mip->y += mip->speed;
            break;
        case 3: // Izquierda
            eraseMip(mip);
            mip->x -= mip->speed;
            break;
        default:
            break;
    }
    drawMip(mip);
}

uint16_t getMipDegree(MipP mip)
{
    return mip->degree;
}


// Seccion Pelota
void drawBall(BallP ball)
{
    drawCircle(ball->radius, ball->color, ball->x, ball->y);
}

void eraseBall(BallP ball)
{
    drawCircle(ball->radius, BACKGROUND_COLOR, ball->x, ball->y);
}

void moveBall(BallP ball, MipP mip)
{
    // Borrar la pelota antes de moverla
    eraseBall(ball);

    // Calcular la nueva posición de la pelota
    switch(mip->degree) {
        case 0: // Arriba
            ball->y -= BALL_INITIAL_SPEED;
            break;
        case 1: // Derecha
            ball->x += BALL_INITIAL_SPEED;
            break;
        case 2: // Abajo
            ball->y += BALL_INITIAL_SPEED;
            break;
        case 3: // Izquierda
            ball->x -= BALL_INITIAL_SPEED;
            break;
        default:
            break;
    }

    // Dibujar la pelota en la nueva posición
    drawBall(ball);
}


// Seccion Agujero
void drawHole(HoleP hole)
{
    drawCircle(hole->radius, HOLE_COLOR, hole->x, hole->y);
}

void eraseHole(HoleP hole)
{
    drawCircle(hole->radius, BACKGROUND_COLOR, hole->x, hole->y);
}

uint8_t checkHoleCollision(BallP ball, HoleP hole)
{
    // Calcular la distancia entre el centro de la pelota y el centro del agujero
    int64_t dx = (int64_t)ball->x - (int64_t)hole->x;
    int64_t dy = (int64_t)ball->y - (int64_t)hole->y;
    
    // Pitagoras
    uint64_t distanceSquared = (dx * dx) + (dy * dy);
    
    // Calcular el radio del agujero al cuadrado
    uint64_t holeRadiusSquared = hole->radius * hole->radius;
    
    // Si la distancia al cuadrado es menor o igual que el radio del agujero al cuadrado,
    // entonces la pelota ha caído en el agujero
    return distanceSquared <= holeRadiusSquared;
}
