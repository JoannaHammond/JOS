[bits 64]
section .data
	val: dq 0   ; define quadword (double precision)

section .text
cos:
    push  rbp
    movsd qword[val], xmm0     ; move "C" param 1 to memory location for val
    fld  qword [val]        ; tell Floating Point Stack to push the contents at memory address of val onto FP Stack (ST0)
    fcos                    ; ask it to calculate the cosine, result put over the original value at ST0
    fstp qword [val]        ; pop the value at ST0 to memory location of val
    movsd xmm0, qword [val]    ; move that memory locations value back to xmm0 for returning;
    pop   rbp
    ret

GLOBAL cos

sin:
    push  rbp
    movsd qword[val], xmm0
    fld  qword [val]
    fsin
    fstp qword [val]
    movsd xmm0, qword [val]
    pop   rbp
    ret

GLOBAL sin

tan:
    push  rbp
    movsd qword[val], xmm0
    fld  qword [val]
    fptan
    fstp qword [val]
    movsd xmm0, qword [val] 
    pop   rbp
    ret

GLOBAL tan