/* sampleCodeModule.c */

#include <videoLib.h>
#include <usrio.h>
#include <shell.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	// puts("Hello, world!");
	// puts("This is a sample code module running in userland.");
	// printf("This is a test of printf: %d, %x, %s\n", 12345, 0xDEADBEEF, "Hello again!");

	// printf("%s", "Testing printf with a string.\n");
	// char str[100];
	// printf("Enter a string: ");
	// scanf("%s", &str);
	// printf("You entered: %s\n", str);

	// char c;
	// while (1)
	// {
	// 	putchar(getchar());
	// }
	
	startShell();

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}