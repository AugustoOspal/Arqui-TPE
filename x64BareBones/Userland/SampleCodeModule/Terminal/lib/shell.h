#ifndef _SHELL_H_
#define _SHELL_H_


typedef enum {HELP = 0, PONGISGOLF, ZOOM_IN, ZOOM_OUT, CLEAR, DATE, REGISTERS, EXIT} command_id;

void startShell();
void readInput();
command_id processInput(char* input);
void help();
void printDateTime();
void notACommand();
void getRegisters();
void exitShell();
void clear_screen();
void startPongis();
void zoom_in();
void zoom_out();

#endif