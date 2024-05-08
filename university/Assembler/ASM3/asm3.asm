;---windows:
;nasm -f win32 -o proga.obj proga.asm
;GoLink.exe /console /entry main proga.obj  msvcrt.dll
%define SUCCESS 0 ; возвращаемое значение функции в случаи успеха
global  start
extern  printf
extern  scanf
extern  exit
section .text
start:
    push    msg
    call    printf
    add esp,4
    push    a
    push    tptd
    call    scanf
    add esp,8
    inc byte [msg_A]
    push    msg
    call    printf
    add esp,4
    push    b
    push    tptd
    call    scanf
    add esp,8
	mov eax, [a]
	mov ebx, [b]
	mov ecx, eax
	cmp eax, ebx
	cmovl eax, ebx
	cmp ebx, ecx
	cmovg ebx, ecx
	push ebx	
	push eax
	push outp
    call    printf
    add esp, 12
    push    SUCCESS
    call    exit
section .data
msg:    db  'enter A:',0
msg_A   equ $ - 3
tptd:   db  '%d',0
outp:    db "%i > %i", 13, 10, 0
a:  dd  0
b:  dd  0