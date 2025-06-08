#include <shell.h>
#include <usrio.h>
#include <usrio.h>
#include <timeLib.h>
#include <stringLib.h>

#define BUFFER 500
#define COMMAND_SIZE 2
#define SPECIAL_KEY_MAX_VALUE 5

// char* commands_str[] = {"help", "date", "exit", "registers"};
char* commands_str[] = {"help", "exit"};

typedef void (*ShellCommand)();
// static ShellCommand commands[] = {help, printDateTime, exitShell, getRegisters};
static ShellCommand commands[] = {help, exitShell};

char *registers[] = {" RAX: ", " RBX: ", " RCX: ", " RDX: ", " RSI: ", " RDI: ", " RBP: ", " RSP: ", " R8: ", " R9: ", " R10: ", " R11: ", " R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};

void show_prompt() {
    printf("user@itba:> ");
}

extern uint64_t *get_regist();

static uint8_t active = 1;

void startShell(){
    char input_buffer[BUFFER];
    while(active) {
        show_prompt();
        readInput(input_buffer);
        to_lower(input_buffer);
        printf(input_buffer);
        command_id command = processInput(input_buffer);
        printf(command);
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
        if(strcmp(input, commands_str[i]) == 0)
            index = i;
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
// void printlDateTime(){
//     // dateTime *dt;
//     // dt = getDateTime();
//     // printf("%d/%d/%d %d:%d:%d\n", dt->day, dt->month, dt->year, dt->hour, dt->min, dt->sec);
// }


void notACommand(char* input){
    printf("Command %s not found. Type 'help' for a list of commands.", input);
}

void getRegisters(){
    printf(" CURRENT REGISTERS VALUES: \n");
    uint64_t *regsValues;
    // regsValues = get_regist();
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