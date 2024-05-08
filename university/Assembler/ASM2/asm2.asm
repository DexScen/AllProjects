extern printf
extern exit
global start

section .data
	a dd 12
	b dd 5
	outp db "%i + %i = %i", 13, 10, 0

section .text
start:
	mov eax, [a]
	mov ebx, [b]
	mov ecx, 0
	add ecx, eax
	add ecx, ebx
	push ecx
	push ebx
	push eax
	push outp
	call printf
	add esp, 16
	push dword 0
	call exit
