section .data
const_a dq 0.35
const_b dq -0.95
const_c dq 2.7

section .text
global f1
f1:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]    ; st0 = x
    fld st0                ; st1 = x
    fmul qword [const_a]   ; st0 = 0.35x
    fmul st1               ; st0 = 0.35x²
    fld qword [const_b]    ; st0 = -0.95, st1 = 0.35x²
    fmul st2               ; st0 = -0.95x
    faddp                  ; st0 = 0.35x² - 0.95x
    fld qword [const_c]    ; st0 = 2.7
    faddp                  ; st0 = 0.35x² - 0.95x + 2.7
    
    pop ebp
    ret


global f2
f2:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]    ; st0 = x
    fld1                   ; st0 = 1, st1 = x
    fld st1                ; st0 = x, st1 = 1, st2 = x
    fld st0                ; st0 = x, st1 = x, st2 = 1, st3 = x
    fadd st0, st1          ; st0 = 2x
    fadd st0, st1          ; st0 = 3x
    fadd st0, st2          ; st0 = 3x + 1
    
    pop ebp
    ret


section .data
const_two dq 2.0
const_one dq 1.0

global f3
f3:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]    ; st0 = x
    fadd qword [const_two] ; st0 = x + 2
    fld1                   ; st0 = 1, st1 = x + 2
    fdivrp                 ; st0 = 1/(x + 2)
    
    pop ebp
    ret


global f1_diff
f1_diff:
    push ebp
    mov ebp, esp

    fld qword [ebp + 8]    ; st0 = x
    fld st0                ; st1 = x
    fmul qword [const_a]   ; st0 = 0.35x
    fadd st0, st0          ; st0 = 0.7x
    fld qword [const_b]    ; st0 = -0.95, st1 = 0.7x
    faddp                  ; st0 = 0.7x - 0.95

    pop ebp
    ret


global f2_diff
f2_diff:
    push ebp
    mov ebp, esp

    fld qword [ebp + 8]    ; st0 = x
    fld1                   ; st0 = 1, st1 = x
    fld1                   ; st0 = 1, st1 = 1, st2 = x
    fld1                   ; st0 = 1, st1 = 1, st2 = 1, st3 = x
    fadd st0, st1          ; st0 = 2
    fadd st0, st1          ; st0 = 3

    pop ebp
    ret


global f3_diff
f3_diff:
    push ebp
    mov ebp, esp

    fld qword [ebp + 8]    ; st0 = x
    fadd qword [const_two] ; st0 = x + 2
    fld st0                ; st1 = x + 2, st0 = x + 2
    fmul st0, st0          ; st0 = (x + 2)^2
    fld1                   ; st0 = 1, st1 = (x + 2)^2
    fchs                   ; st0 = -1, st1 = (x + 2)^2
    fdivrp                 ; st0 = -1 / (x + 2)^2

    pop ebp
    ret