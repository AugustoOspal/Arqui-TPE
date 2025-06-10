#include <shell.h>
#include <usrio.h>
#include <timeLib.h>
#include <stringLib.h>
#include <pongisLib.h>
#include <videoLib.h>


#define BUFFER 500
#define COMMAND_SIZE 8
#define SPECIAL_KEY_MAX_VALUE 5

char* commands_str[] = {"help", "pongisgolf", "zoom in", "zoom out", "clear", "date", "registers", "exit"};


typedef void (*ShellCommand)();
static ShellCommand commands[] = {help, startPongis , zoom_in, zoom_out, clear_screen, printDateTime, getRegisters, exitShell};


char *registers[] = {" RAX: ", " RBX: ", " RCX: ", " RDX: ", " RSI: ", " RDI: ", " RBP: ", " RSP: ", " R8: ", " R9: ", " R10: ", " R11: ", " R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};

void show_prompt() {
    printf("user@itba:> ");
}

static uint8_t active = 1;

void startShell(){
    char input_buffer[BUFFER];
    while(active) {
        show_prompt();
        readInput(input_buffer);
        to_lower(input_buffer);
        command_id command = processInput(input_buffer);
        if(command != -1) {
             commands[command]();
         }else {
             notACommand(input_buffer);
         }
    }
}

// Falta implementar la syscall read // 
void readInput(char *buffer){
    char * c = buffer;
    int limit_count = 0;

    do {
        *c = getchar();
        if(*c <= SPECIAL_KEY_MAX_VALUE) {
            c--;
        } else if(*c == '\b') {
            if(c > buffer) {
                putchar(*c);
                c--;
            }
            c--;
        }else {
            putchar(*c);
            limit_count++;
            if(limit_count > BUFFER)
                break;
        }
    } while((*c++) != '\n');
    *(c-1) = '\0';
}

command_id processInput(char* input){
    int index = -1;
    for(int i = 0; i < COMMAND_SIZE && (index == -1); i++) {
        if(strcmp(input, commands_str[i]) == 0){
            index = i;
        }
    }
    return index;
}

// Imprime todos los comandos disponibles // 
void help(){
    printf("Commands:\n");
    for(int i = 0; i < COMMAND_SIZE; i++) {
        printf("\t- %s\n", commands_str[i]);
    }
}

// Faltan las syscals del dateTime // 
void printDateTime(){
    dateTime dt;
    getDateTime(&dt);
    printf(" %d/%d/%d %d:%d:%d\n", dt.day, dt.month, dt.year, dt.hour, dt.min, dt.sec);
}

void startPongis(){
    printf("Starting Pongis Golf...\n");
    startPongisGolf();
}

void notACommand(char* input){
    printf("Command \"%s\" not found. Type 'help' for a list of commands.\n", input);
}

void getRegisters(){
    printf(" CURRENT REGISTERS VALUES: \n");
    uint64_t regsValues[17];
    get_regist(regsValues);
    for (int i = 0; i < 17; i++){
            printf("%s %x\n",registers[i], regsValues[i]);
    }   
}

void clear_screen() {
    clearScreen();
}

void zoom_in() {
    zoomIn();
}

void zoom_out() {
    zoomOut();
}

void exitShell(){
    printf("\n");
    printf("Exiting...\n");

    printf("\n[Exit succesful]\n");
    active = 0;
}

