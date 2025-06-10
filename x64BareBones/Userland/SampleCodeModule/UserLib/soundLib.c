#include <soundLib.h>

void playSound(uint32_t frequency, uint32_t duration) {
    sys_playSound(frequency, duration);
}

void playHitSound()
{
    // Sonido de "thud" cuando el MIP golpea la pelota
    playSound(300, 50);   // Tono bajo y corto
    playSound(250, 50);   // Seguido de otro más grave
}

void playStartMusic()
{
    // Melodía de inicio - secuencia ascendente alegre
    playSound(262, 150);  // Do
    playSound(294, 150);  // Re
    playSound(330, 150);  // Mi
    playSound(349, 150);  // Fa
    playSound(392, 200);  // Sol (más largo)
    playSound(440, 150);  // La
    playSound(523, 300);  // Do alto (final triumfante)
}

void playHoleMusic()
{
    // Melodía de victoria cuando la pelota entra al hoyo
    playSound(523, 200);  // Do alto
    playSound(659, 200);  // Mi alto
    playSound(784, 200);  // Sol alto
    playSound(1047, 400); // Do súper alto (climax)
    
    // Pequeña pausa
    playSound(0, 100);
    
    // Acorde final
    playSound(523, 600);  // Do largo para cerrar
}