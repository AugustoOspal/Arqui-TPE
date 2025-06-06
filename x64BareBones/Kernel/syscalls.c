#include <syscalls.h>


// No esta terminado, es un ejemplo nada mas
static void sys_write(uint64_t fd, const char *str, uint64_t count) 
{

}

void syscallDispatcher(Registers_t *regs) 
{
    // El número de la syscall generalmente se pasa en RAX
    uint64_t syscall_id = regs->rax;

    // Los argumentos suelen pasarse en RDI, RSI, RDX, RCX, R8, R9 (según la convención de llamada de System V AMD64)
    uint64_t arg1 = regs->rdi;
    uint64_t arg2 = regs->rsi;
    uint64_t arg3 = regs->rdx;
    uint64_t arg4 = regs->rcx;
    uint64_t arg5 = regs->r8;
    uint64_t arg6 = regs->r9;

    /*
        Las que son 0x1... son syscalls de video
        Las que son 0x2... son syscalls de teclado
    */

    switch (syscall_id) 
    {
        case 1: 
            sys_write(arg1, (const char *)arg2, arg3);
            regs->rax = arg1; // Bytes escritos
            break;

        case 0x10:
            clearScreen();
            regs->rax = 0;
            break;

        case 0x11:
            putPixel((uint32_t)arg1, arg2, arg3);
            regs->rax = 0;
            break;

        case 0x12:
            drawChar((char)arg1, (uint32_t)arg2, arg3, arg4);
            regs->rax = 0;
            break;

        case 0x13:
            drawString((const char *)arg1, (uint32_t)arg2, arg3, arg4);
            regs->rax = 0;
            break;

        case 0x14:
            drawRectangle(arg1, arg2, (uint32_t)arg3, arg4, regs->r8);
            regs->rax = 0;
            break;

        case 0x15:
            drawDecimal(arg1, (uint32_t)arg2, arg3, arg4);
            regs->rax = 0;
            break;

        case 0x16:
            drawHexa(arg1, (uint32_t)arg2, arg3, arg4);
            regs->rax = 0;
            break;

        case 0x17:
            drawBin(arg1, (uint32_t)arg2, arg3, arg4);
            regs->rax = 0;
            break;

        case 0x18:
            regs->rax = getScreenWidth();
            break;

        case 0x19:
            regs->rax = getScreenHeight();
            break;

        case 0x20:
            regs->rax = kbd_get_char();
            break;

        default:
            // Syscall desconocida o no implementada
            // Se imprime un error o se establece un código de error en rax
            regs->rax = (uint64_t)-1; // Ejemplo de error (ENOSYS)
            break;
    }
}