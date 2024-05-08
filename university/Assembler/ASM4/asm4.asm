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
; nachalo

mov ax,1             ;В EAX будет факториал, на это число мы будем умножать все остальные. 
mov cx,[a]       ; В ECX число факториал которого нужно найти. 
 
factCycle:
mul cx                ; умножаем eax на ecx
dec cx                ; вычитаем из ecx еденицу
cmp cx,1         ; проверяем не равен ли ECX еденице
jne factCycle     ; JNE= JUMP if  NOT EQUAL - переход если неравно.  если ECX != 1 - переходим на следующую итерацию.

mov ebx, [a]
push eax	
push ebx
push outp
call    printf
add esp, 12
push    SUCCESS
call    exit
section .data
msg:    db  'enter A:',0
tptd:   db  '%d',0
outp:    db "%i!=%i", 13, 10, 0
a:  dd  0
res:  dd  0