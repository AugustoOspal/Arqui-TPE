GLOBAL read_sys
GLOBAL write_sys
GLOBAL get_date_time_sys
GLOBAL screen_clear_sys
GLOBAL change_color_sys
GLOBAL zoom_sys	

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
; Funcion : read_sys
;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Argumentos:
;   1 - buffer
;   2 - count
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

read_sys:
    pushState

    mov rax, ; Syscall number for read
    mov rdx, rsi        ;cargo argumento count
	mov rsi, rdi		;cargo argumento buffer
	mov rdi, 0x00
    int 80h

    popState
    
    ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Funcion : write_stdin_sys
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Argumentos:
;   1 - string
;   2 - count
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

write_sys:
    pushState

    mov rax, ; Syscall number for write
	mov rdx, rsi    ;cargo argumento count
    mov rsi, rdi    ;cargo argumento string
	mov rdi, 0x01
    int 80h

    popState
    
    ret


;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : get_date_time_sys 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

get_date_time_sys: 
	pushState
	mov rax, ; Syscall number for get_date_time
	int 80h
	popState

	ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : screen_clear_sys 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

screen_clear_sys: 
	pushState
	mov rax, ; Syscall number for screen_clear
	int 80h
	popState

	ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : change_color_sys 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

change_color_sys:
	pushState
	
	mov rax, ; Syscall number for change_color
	int 80h
	
	popState
	
	ret

;$$$$$$$$$$$$$$$$$$$$$$$$$$$
; Function : zoom_sys 
;$$$$$$$$$$$$$$$$$$$$$$$$$$$

zoom_sys:
	pushState

	mov rax, ; Syscall number for zoom
	int 80h

	popState

	ret

