;DRAFT ONLY

section .data

section .text
bits 64
default rel

global nonsimd_stencil
extern printf

nonsimd_stencil:
    ; Prologue
    push rbp
    mov rbp, rsp

    ; Function parameters:
    ; rdi - pointer to X
    ; rsi - pointer to Y
    ; rdx - length of the vector n

    mov r8, rdx          ; Store length of vector n in r8
    sub r8, 3            ; Calculate n - 3

    mov rcx, 3           ; Start index i from 3

.loop:
    ; Check if we've reached the end of the array (i >= n - 3)
    cmp rcx, r8
    jge .done

    ; Perform the stencil operation:
    ; Y[i] = X[i-3] + X[i-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]
    mov eax, [rdi + 4*rcx - 12]  ; X[i-3]
    add eax, [rdi + 4*rcx - 8]   ; X[i-2]
    add eax, [rdi + 4*rcx - 4]   ; X[i-1]
    add eax, [rdi + 4*rcx]       ; X[i]
    add eax, [rdi + 4*rcx + 4]   ; X[i+1]
    add eax, [rdi + 4*rcx + 8]   ; X[i+2]
    add eax, [rdi + 4*rcx + 12]  ; X[i+3]

    ; Store the result in Y[i]
    mov [rsi + 4*rcx], eax

    ; Increment the index
    inc rcx
    jmp .loop

.done:
    ; Epilogue
    mov rsp, rbp
    pop rbp
    ret
