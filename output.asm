section .data
x dd 0
; Square operation macro
%macro square 1
    ; Save operand
    mov ebx, %1
    ; Square the value
    imul %1, ebx
%endmacro

section .text
global _main
extern _printf
extern _ExitProcess@4

_main:
    push ebp
    mov ebp, esp
    mov eax, 5
    square eax
    mov [x], eax
    push eax
    push dword [x]
    push dword fmt
    call _printf
    add esp, 12
    pop eax
    push 0
    call _ExitProcess@4
    mov esp, ebp
    pop ebp
    ret

section .data
fmt db 'Result: %d', 10, 0
