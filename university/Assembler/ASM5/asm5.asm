extern  printf
extern  exit
extern _invertible
global start

section .text
start:
    push dword 13
    push dword 124
    call _invertible
    cmp eax, 137
    je plus
    cmp eax, 111
    je minus
    cmp eax, 1612
    je mult
    cmp eax, 9
    je div
    cmp eax, 7
    je rem
    cmp eax, 12
    je andb
    cmp eax, 125
    je orb

then:
    push xorcase
    jmp endif

plus:
    push pluscase
    jmp endif

minus:
    push minuscase
    jmp endif

mult:
    push multcase
    jmp endif

div:
    push divcase
    jmp endif

rem:
    push remcase
    jmp endif

andb:
    push andcase
    jmp endif

orb:
    push orcase
    jmp endif

endif:
    call printf
    add esp, 4
    push dword 0
    call exit

section .data
pluscase db '+', 13, 10, 0
minuscase db '-', 13, 10, 0
multcase db '*', 13, 10, 0
divcase db '/', 13, 10, 0
remcase db '%%', 13, 10, 0
andcase db '&', 13, 10, 0
orcase db '|', 13, 10, 0
xorcase db '^', 13, 10, 0