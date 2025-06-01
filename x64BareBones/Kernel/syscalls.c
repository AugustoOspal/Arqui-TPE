#include <syscalls.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <stddef.h>

// No esta terminado, es un ejemplo nada mas
static void sys_write(uint64_t fd, const char *str, uint64_t count) 
{
    switch(fd){
        case STDOUT:
            for (uint64_t i = 0; i < count; i++) {
                ncPrintChar(str[i]);
            }
            break;
        case STDERR:
            for (uint64_t i = 0; i < count; i++) {
                ncPrintChar(str[i]);
            }
            break;
        default:
            break;
    }
}

static void sys_read(FD fd, const char *buffer, size_t count) 
{
    switch(fd){
        case STDIN:
            load_buffer(buffer, count);
            break;
        default:
            break;
    }
}

static void sys_screen_clear()
{
    clearScreen();
}

void syscallDispatcher(Registers_t *regs) 
{
    // El número de la syscall generalmente se pasa en RAX
    uint64_t syscall_id = regs->rax;

    // Los argumentos suelen pasarse en RDI, RSI, RDX, R10, R8, R9 (según la convención de llamada de System V AMD64)
    uint64_t arg1 = regs->rdi;
    uint64_t arg2 = regs->rsi;
    uint64_t arg3 = regs->rdx;
    uint64_t arg4 = regs->rcx;
    // ...

    switch (syscall_id) 
    {
        case 1: 
            sys_write(arg1, (const char *)arg2, arg3);
            regs->rax = arg1; // Bytes escritos
            break;
        
        // case 2: 
            
        // case 3: 

        // case 4: 

        // case 5: 

        // case 6: 

        // case 7: 

        // case 8: 

        default:
            // Syscall desconocida o no implementada
            // Se imprime un error o se establece un código de error en rax
            regs->rax = (uint64_t)-1; // Ejemplo de error (ENOSYS)
            break;
    }
}