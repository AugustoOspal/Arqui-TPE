/* sampleCodeModule.c */

#include <lib.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	putPixel(0xFF0000, 10, 10);
	drawRectangle(100, 50, 0x0000FF, 20, 20);
	drawDecimal(123456789, 0xFFFF00, 30, 30);
	drawHexa(0xABCDEF, 0x00FFFF, 40, 40);
	drawBin(0b101010101010, 0xFF00FF, 50, 50);
	drawChar('A', 0xFFFFFF, 60, 60);
	drawString("Hello from SampleCodeModule!", 0x00FF00, 0, 0);

	char c;

	// TODO: Arreglar getChar() que no funciona bien
	while (!(c = getChar())) {
		if (c == 'q') {
			break; // Exit on 'q'
		}
		drawChar(c, 0xFFFFFF, 80, 80);
	}
	

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}