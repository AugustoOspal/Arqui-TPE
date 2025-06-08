#ifndef _SHELL_H_
#define _SHELL_H_

typedef enum {HELP = 0, EXIT, REGISTERS} command_id;

void startShell();
void readInput();
command_id processInput(char* input);
void excecuteCommand(command_id command);
void help();
void printDateTime();
void notACommand();
void getRegisters();
void exitShell();

#endif