GLOBAL cpuVendor
GLOBAL getSysSeconds
GLOBAL getSysMinutes
GLOBAL getSysHours
GLOBAL getSysDayOfWeek
GLOBAL getSysDayOfMonth
GLOBAL getSysMonth
GLOBAL getSysYear

GLOBAL getKeyCode

; Lo usamos para sonido nosotros
GLOBAL outb
GLOBAL inb

GLOBAL refresh_registers
GLOBAL get_registers

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


;Funcionalidades del RTC

; Recibe en al el numero y lo devuelve
; en al pasado a decimal.
; Si por ejemplo la entrada es
; 0100 0101, los primeros 4 bits
; representan un 4 y los otros un 5,
; asi que devolvemos 45
convertBCDtoDec:
	push rbp			; Armado del stackframe
	mov rbp, rsp		;

	push rbx			; Back up de los registros
	push rcx			;
	push rdx			;

	mov rbx, 0			; Limpio registros
	mov rcx, 0			;

	mov bl, al			; Backup del original

	and al, 0x0F		; Agarro los 4 lsb
	mov cl, al			; los guardo en cl

	mov al, bl			; Agarro el numero original
	shr al, 4			; Muevo los 4 msb a la derecha

	mov bl, 10
	mul bl				; Multiplica por 10 al

	add al, cl			; Le agrega lo calculado antes		

	pop rdx
	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp 
	ret

getSysSeconds:
	push rbp
	mov rbp, rsp

	mov al, 0

	out 70h, al
	in al, 71h

	call convertBCDtoDec

	mov rsp, rbp
	pop rbp
	ret


getSysMinutes:
	push rbp
	mov rbp, rsp

	mov al, 2

	out 70h, al
	in al, 71h

	call convertBCDtoDec

	mov rsp, rbp
	pop rbp
	ret

getSysHours:
	push rbp
	mov rbp, rsp

	mov al, 4

	out 70h, al
	in al, 71h

	call convertBCDtoDec

	mov rsp, rbp
	pop rbp
	ret

getSysDayOfWeek:
	push rbp
	mov rbp, rsp

	mov al, 6

	out 70h, al
	in al, 71h

	call convertBCDtoDec 

	mov rsp, rbp
	pop rbp
	ret

getSysDayOfMonth:
	push rbp
	mov rbp, rsp

	mov al, 7

	out 70h, al
	in al, 71h

	call convertBCDtoDec 

	mov rsp, rbp
	pop rbp
	ret

getSysMonth:
	push rbp
	mov rbp, rsp

	mov al, 8

	out 70h, al
	in al, 71h

	call convertBCDtoDec 

	mov rsp, rbp
	pop rbp
	ret

getSysYear:
	push rbp
	mov rbp, rsp

	mov al, 9

	out 70h, al
	in al, 71h

	call convertBCDtoDec 

	mov rsp, rbp
	pop rbp
	ret


getKeyCode:
	push rbp
	mov rbp, rsp
	
	mov rax, 0      ; Valor de retorno por defecto: 0 (ningún carácter / no imprimible)

	in al, 64h		; Leer el puerto de estado del controlador del teclado (flags)
	test al, 0x01	; Comprobar el bit 0 (Output Buffer Full - OBF)
	jz .exit_gk		; Si no está lleno (no hay tecla), saltar al final (RAX ya es 0)

	; Una tecla está disponible, leerla
	in al, 60h 		; Leer el scancode del puerto de datos del teclado

.exit_gk:
	mov rsp, rbp
	pop rbp
	ret

outb:
    mov dx, di
    mov al, sil 
    out dx, al
    ret

inb:
    mov dx, di 
    in al, dx
    movzx rax, al
    ret

refresh_registers:
    ; No lo pusheo para que no lo afecte
    mov [registers], rax
    mov [registers + 1*8], rbx
    mov [registers + 2*8], rcx
    mov [registers + 3*8], rdx
    mov [registers + 4*8], rsi
    mov [registers + 5*8], rdi
    mov [registers + 6*8], rbp
    mov [registers + 7*8], r8
    mov [registers + 8*8], r9
    mov [registers + 9*8], r10
    mov [registers + 10*8], r11
    mov [registers + 11*8], r12
    mov [registers + 12*8], r13
    mov [registers + 13*8], r14
    mov [registers + 14*8], r15

    mov rax, [rsp]          	; Lee RIP
    mov [registers + 15*8], rax ; Guardo RIP

    mov rax, rsp
    mov [registers + 16*8], rax
    ret


get_registers:
    mov rax, registers
    ret

section .bss
    registers resq 17