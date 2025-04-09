
section .data
    format db "%d", 10, 0

section .text
    global main
    extern printf

main:
    mov eax, 5
    ; SQUARE instruction: i * i
    mov eax, eax
    mul eax
    mov ebx, eax
    push ebx
    push format
    call printf
    add esp, 8

    ret
