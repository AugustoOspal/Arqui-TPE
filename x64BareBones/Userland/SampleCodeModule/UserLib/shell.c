#include <shell.h>
#include <lib.h>

#define BUFFER 500
#define COMMAND_SIZE 4


char* commands_str[] = {"help", "date", "exit", "registers"};

typedef void (*ShellCommand)();
static ShellCommand commands[] = {help, printDateTime, exitShell, getRegisters};

char *registers[] = {" RAX: ", " RBX: ", " RCX: ", " RDX: ", " RSI: ", " RDI: ", " RBP: ", " RSP: ", " R8: ", " R9: ", " R10: ", " R11: ", " R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};

void show_prompt() {
    printf("user@itba:> ");
}

extern void get_regist(uint64_t *registers);

static uint8_t active = 1;

void startShell(){
    char input_buffer[BUFFER];
    while(active) {
        show_prompt();
        readInput(input_buffer);
        to_lower(input_buffer);
        command_id command = processInput(input_buffer);
        if(command != -1) {commands[command]();}
    }
}

// Falta implementar la syscall read // 
void readInput();
command_id processInput(char* input);
void excecuteCommand(command_id command);

// Imprime todos los comandos disponibles // 
void help(){
    printf("Commands:\n");
    for(int i = 0; i < COMMAND_SIZE; i++) {
        printf("\t- %s\n", commands_str[i]);
    }
}

// Faltan las syscals del dateTime // 
void printlDateTime(){
    dateTime *dt;
    getDateTime(dt);
    printf("%d/%d/%d %d:%d:%d\n", dt->day, dt->month, dt->year, dt->hour, dt->min, dt->sec);
}


void notACommand(){
    printf("Command not found. Type 'help' for a list of commands.");
}

void getRegisters(){
    printf(" CURRENT REGISTERS VALUES: \n");
    uint64_t regsValues[17];
    get_regist(regsValues);
    for (int i = 0; i < 17; i++){
            printf("\n%s %x",registers[i], regsValues[i]);
    }   
    printf("\n");
}

void exitShell(){
    printf("\n");
    printf("Exiting...\n");
    printf("\n");

    printf("\n[Exit succesful]\n");
    active = 0;
}