GLOBAL sys_clearScreen
GLOBAL sys_putPixel
GLOBAL sys_drawChar
GLOBAL sys_drawString
GLOBAL sys_drawRectangle
GLOBAL sys_drawDecimal
GLOBAL sys_drawHexa
GLOBAL sys_drawBin
GLOBAL sys_getScreenWidth
GLOBAL sys_getScreenHeight

GLOBAL sys_kbdGetChar

GLOBAL sys_write
GLOBAL sys_read

GLOBAL sys_getRegisters
GLOBAL sys_getTime

section .text

%macro syscall 1
    mov rax, %1
    int 80h
    ret
%endmacro

sys_write:              syscall 0x1
sys_read:               syscall 0x2

sys_getRegisters:       syscall 0x04
sys_getTime:            syscall 0x05  

; Video
sys_clearScreen:        syscall 0x10
sys_putPixel:           syscall 0x11
sys_drawChar:           syscall 0x12
sys_drawString:         syscall 0x13
sys_drawRectangle:      syscall 0x14
sys_drawDecimal:        syscall 0x15
sys_drawHexa:           syscall 0x16
sys_drawBin:            syscall 0x17
sys_getScreenWidth:     syscall 0x18
sys_getScreenHeight:    syscall 0x19

; Teclado
sys_kbdGetChar:         syscall 0x20
	