#ifndef _KEYBOARDDRIVER_H_
#define _KEYBOARDDRIVER_H_

// Función que se llama desde el IRQ dispatcher
void keyboard_handler(); 

// Función para que las aplicaciones/kernel obtengan un carácter del buffer
// Retorna 0 si el buffer está vacío.
// TODO: Hacer una syscall para que se pueda acceder desde userland
char kbd_get_char();

// Función de ASM para leer el scancode raw del puerto del teclado
extern unsigned int getKeyCode();

#endif