#include <stdint.h>

#include <time.h>
#include <keyboardDriver.h>

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq) {

	// TODO: Esto depues hay que pasarlo a un array

	switch (irq) {

		// Timer Tick
		case 0:
			int_20();
			break;

		// Teclado
		case 1:
			int_21();
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}

void int_21(){
	keyboard_handler();

	// Tester
	char c = kbd_get_char();
	if (c)
	{
		clearScreen(); // Limpia la pantalla antes de dibujar el carácter
		drawChar(c, 0xFFFFFF, 0, 0); // Dibuja el carácter en la posición (0, 0) con color blanco
	}
}
