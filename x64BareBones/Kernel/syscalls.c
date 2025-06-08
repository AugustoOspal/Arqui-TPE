#include <syscalls.h>

#define STDIN  0
#define STDOUT 1

#define VERDE   0x8bd450
#define VIOLETA 0x8b4bd4
#define BLANCO  0xffffff
#define NEGRO   0x000000

#define TAB_SPACES 4

// Coordinadas del cursor
static uint16_t x_coord = 0;
static uint16_t y_coord = 0;

extern uint64_t registers[];
extern void load_registers();


uint8_t isSpecialChar(char c) 
{
    return (c == '\n' || c == '\r' || c == '\t' || c == '\b');
}

uint64_t sys_write(uint8_t fd, const char *str, uint64_t count) 
{
    // Solo se soporta escritura en STDOUT
    if (fd != STDOUT) 
        return 0; 

    for (uint64_t i = 0; i < count; i++) 
    {
        if (isSpecialChar(str[i])) 
        {
            switch (str[i]) 
            {
            case '\n':
                y_coord += FONT_CHAR_HEIGHT_BYTES + FONT_CHAR_GAP;
        
            case '\r':
                x_coord = 0;
                break;

            case '\t':
                x_coord += (TAB_SPACES * (FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP));
                if (x_coord >= getScreenWidth()) 
                {
                    x_coord = x_coord % getScreenWidth();
                    y_coord += FONT_CHAR_HEIGHT_BYTES + FONT_CHAR_GAP;
                }
                break;

            case '\b':

                if (x_coord > FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP) 
                {
                    x_coord -= (FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP);
                } 
                else 
                {
                    if (y_coord > 0) 
                    {
                        y_coord -= (FONT_CHAR_HEIGHT_BYTES + FONT_CHAR_GAP);
                        x_coord = getScreenWidth() - TAB_SPACES*(FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP) + x_coord;
                    } 
                    else 
                    {
                        x_coord = 0;
                    }
                }

                // TODO: Esto en vez del un espacio tendria que ser un caracter con todo
                // el bit map en 1. Tambien sirve para el cursor
                drawRectangle(FONT_CHAR_WIDTH_BYTES, FONT_CHAR_HEIGHT_BYTES, NEGRO, x_coord, y_coord);
                break;
            }
        } 

        // TODO: Aca se podria optimizar con getRemainingScreenWidth
        else if (isValidScreenPrint(x_coord, y_coord, FONT_CHAR_WIDTH_BYTES, FONT_CHAR_HEIGHT_BYTES)) 
        {
            drawChar(str[i], BLANCO, x_coord, y_coord);
            x_coord += FONT_CHAR_WIDTH_BYTES + FONT_CHAR_GAP;
        } 
        else 
        {
            x_coord = 0;
            y_coord += FONT_CHAR_HEIGHT_BYTES + FONT_CHAR_GAP;
        }
    }

    return count;
}

uint64_t sys_read(uint8_t fd, char *buffer, uint64_t count)
{
    if(fd == STDIN)
    {
        char c;

        for (uint64_t i = 0; i < count; i++)
        {
            if (!(c = kbd_get_char()))
                return i;

            buffer[i] = c;
        }
        
        return count;
    }

    return 0;
}

// void getTime(dateTime *dt) 
// {
//     dt->sec = getSysSeconds();
//     dt->min = getSysMinutes();
//     dt->hour = getSysHours();
//     dt->day = getSysDayOfWeek();
//     dt->month = getSysMonth();
//     dt->year = getSysYear();
// }

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
    */

    switch (syscall_id) 
    {
        case 0x1: 
            sys_write(arg1, (const char *)arg2, arg3);
            regs->rax = arg1;
            break;

        case 0x2:
            regs->rax = sys_read(arg1, (char *)arg2, arg3);
            break;

        case 0x04:
            uint64_t *regsValues = (uint64_t *)arg1;
            for(int i = 0; i < 17; i++) {
                load_registers();
                regsValues[i] = registers[i];
            }
            regs->rax = 0;
            break;

        // case 0x05:
        //     dateTime *dt;
        //     getTime(dt);
        //     regs->rax = dt;
        //     break;

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

        case 0x30:
            playSoundForDuration((uint32_t)arg1, (uint32_t)arg2);
            regs->rax = 0;
            break;

        case 0x40:
            sleep(arg1);
            regs->rax = 0;
            break;

        default:
            // Syscall desconocida o no implementada
            // Se imprime un error o se establece un código de error en rax
            regs->rax = (uint64_t)-1; // Ejemplo de error (ENOSYS)
            break;
    }
}