GLOBAL read
GLOBAL write_stdin
GLOBAL get_date_time
GLOBAL screen_clear
GLOBAL change_color
GLOBAL zoom

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Funcion : read
;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Argumentos:
;   1 - buffer
;   2 - count
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

read:
    pushState

    mov rax, ; Syscall number for read
    mov rdx, rsi        ;cargo argumento count
	mov rsi, rdi		;cargo argumento buffer
	mov rdi, 0x00
    int 80h

    popState
    
    ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Funcion : write_stdin
;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Argumentos:
;   1 - string
;   2 - count
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

write_stdin:
    pushState

    mov rax, ; Syscall number for write
	mov rdx, rsi    ;cargo argumento count
    mov rsi, rdi    ;cargo argumento string
	mov rdi, 0x01
    int 80h

    popState
    
    ret


;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : get_date_time 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

get_date_time: 
	pushState
	mov rax, ; Syscall number for get_date_time
	int 80h
	popState

	ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : screen_clear 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

screen_clear: 
	pushState
	mov rax, ; Syscall number for screen_clear
	int 80h
	popState

	ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : change_color 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

change_color:
	pushState
	
	mov rax, ; Syscall number for change_color
	int 80h
	
	popState
	
	ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : zoom 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

zoom:
	pushState

	mov rax, ; Syscall number for zoom
	int 80h

	popState

	ret

