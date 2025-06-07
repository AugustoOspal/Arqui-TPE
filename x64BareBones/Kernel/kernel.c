#include <lib.h>
#include <stdint.h>
#include <string.h>
#include <fonts.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <moduleLoader.h>
#include <idtLoader.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main()
{	
	load_idt();

	// char c;
	// uint32_t x_pos = 0;

	// while (1)
	// {
	// 	if (c = kbd_get_char())
	// 	{
	// 		if (c == 'q') {
	// 			break; // Exit on 'q'
	// 		}
	// 		drawChar(c, 0xFFFFFF, x_pos, 80);
	// 		x_pos += FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP;
	// 	}
	// }
	

	return ((EntryPoint)sampleCodeModuleAddress)();
}
