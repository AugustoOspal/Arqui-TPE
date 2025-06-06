GLOBAL sys_DrawString

section .text

%macro syscall 1
    mov rax, %1
    int 80h
    ret
%endmacro

sys_DrawString: syscall 12