section .data
    format: db "%d", 10, 0  ; format string for printf

section .bss
    str: resb 256  ; allocate 256 bytes for the string

section .text
    global main
    extern printf

; ft_len function
ft_len:
    push ebp
    mov ebp, esp
    mov eax, 0      ; i = 0
    mov ecx, [ebp+8]  ; ecx = str
len_loop:
    cmp byte [ecx+eax], 0  ; check if str[i] == '\0'
    je len_exit
    inc eax         ; i++
    jmp len_loop
len_exit:
    mov esp, ebp
    pop ebp
    ret

; main function
main:
    push ebp
    mov ebp, esp
    sub esp, 4      ; allocate space for a pointer
    lea eax, [ebp-4]  ; eax = &str
    mov [eax], dword str  ; str = address of the 'str' variable
    push dword [eax]  ; push str as argument
    call ft_len     ; call ft_len(str)
    add esp, 4      ; remove the argument from the stack
    push eax        ; push the result as argument for printf
    push dword format  ; push the format string as argument for printf
    call printf     ; call printf(format, result)
    add esp, 8      ; remove the arguments from the stack
    mov esp, ebp
    pop ebp
    xor eax, eax    ; return 0
    ret
