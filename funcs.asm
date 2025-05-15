section .note.GNU-stack noalloc noexec nowrite progbits

section .data
const_a dq 0.35
const_b dq -0.95
const_c dq 2.7
const_two dq 2.0
const_one dq 1.0
const_three dq 3.0


section .text
global f1
f1:
    push ebp
    mov ebp, esp
    fld qword [ebp+8]     ; x
    fld qword [const_a]   ; 0.35
    fmulp st1, st0        ; 0.35*x
    fld qword [ebp+8]     ; x
    fmulp st1, st0        ; 0.35*x²
    fld qword [const_b]   ; -0.95
    fmul qword [ebp+8]    ; -0.95*x
    faddp st1, st0        ; 0.35*x² - 0.95*x
    fld qword [const_c]   ; 2.7
    faddp st1, st0        ; итоговый результат
    pop ebp
    ret

global f2
f2:
    push ebp
    mov ebp, esp

    fld qword [ebp + 8]    ; Загружаем x
    fld qword [const_three] ; Загружаем 3.0
    fmulp st1, st0         ; 3*x
    fld qword [const_one]   ; Загружаем 1.0
    faddp st1, st0         ; 3*x + 1
    
    pop ebp
    ret

global f3
f3:
    push ebp
    mov ebp, esp
    fld qword [ebp + 8]
    fadd qword [const_two]
    fld1
    fdivrp
    pop ebp
    ret

global f1_diff
f1_diff:
    push ebp
    mov ebp, esp
    fld qword [ebp + 8]
    fld st0
    fmul qword [const_a]
    fadd st0, st0
    fld qword [const_b]
    faddp
    pop ebp
    ret

global f2_diff
f2_diff:
    push ebp
    mov ebp, esp
    fld qword [const_three]   ; Просто загружаем константу 3.0
    pop ebp
    ret


global f3_diff
f3_diff:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]   
    fadd qword [const_two]
    fld st0               
    fmulp st1, st0        
    fld1
    fchs                  
    fdivrp st1, st0
    
    pop ebp
    ret
