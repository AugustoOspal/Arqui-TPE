#include <stdint.h>
#include <videoDriver.h>
#include <syscalls.h>
#include <color.h>
#include <fonts.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPERATION_CODE_ID 6
#define CANT_REGS 20

static void zero_division();
static void invalid_operation_code();
void printRegisters();

static const char* regs_strings[] = {
    "R15", "R14", "R13", "R12", "R11", "R10", "R9 ", "R8 ",
    "RSI", "RDI", "RBP", "RDX", "RCX", "RBX", "RAX",
    "RIP", "CS ", "FLG", "RSP", "SS "
};

void exceptionDispatcher(int exception) {
	switch (exception){
		case ZERO_EXCEPTION_ID:
			zero_division();
			break;
		case INVALID_OPERATION_CODE_ID:
			invalid_operation_code();
			break;
	}
	printRegisters();
}


static void zero_division() {
	clearScreen();
	drawString("ZERO DIVISION ERROR", RED, 0, 0);
}

static void invalid_operation_code(){
	clearScreen();
	drawString("INVALID OPERATION CODE ERROR", RED, 0, 0);
}

void printRegisters(){
	unsigned int linesPrinted = 1;
	unsigned int currentY = 0;

	uint64_t *regs = get_registers();

	for (int i = 0; i < CANT_REGS; i++) {
		currentY = (getCurrentFontHeight() + FONT_CHAR_GAP) * linesPrinted++;
		drawString(regs_strings[i], RED, 0, currentY);
		drawHexa(regs[i], RED, 10 * (getCurrentFontWidth() + FONT_CHAR_GAP), currentY);
	}
}	
