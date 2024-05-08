extern printf
extern exit
global start

section .text
start:
	push msg
	call printf
	add esp, 4
	push dword 0
	call exit

section .data
msg: db 'hello world', 13, 10, 0
