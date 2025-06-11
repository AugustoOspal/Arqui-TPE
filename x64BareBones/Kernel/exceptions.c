#include <stdint.h>
#include <videoDriver.h>
#include <syscalls.h>
#include <color.h>
#include <fonts.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPERATION_CODE_ID 6
#define CANT_REGS 17

static void zero_division();
static void invalid_operation_code();
void printRegisters();

char* regs_strings[] = {" RAX: ", " RBX: ", " RCX: ", " RDX: ", " RSI: ", " RDI: ", 
						" RBP: ", " RSP: ", " R8: ", " R9: ", " R10: ", " R11: ", 
						" R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};


void exceptionDispatcher(int exception) {
	refresh_registers();
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
	drawString("ZERO DIVISION ERROR", 0xFF0000, 0, 0);
}

static void invalid_operation_code(){
	clearScreen();
	drawString("INVALID OPERATION CODE ERROR", 0xFF0000, 0, 0);
}

void printRegisters(){
	unsigned int linesPrinted = 0;
	unsigned int currentY = 0;

	uint64_t *regs = get_registers();

	for (int i = 0; i < CANT_REGS; i++) {
		currentY = (getCurrentFontHeight() + FONT_CHAR_GAP) * linesPrinted++;
		drawString(regs_strings[i], RED, 0, currentY);
		drawHexa(regs[i], RED, 10, currentY);
	}
}	
