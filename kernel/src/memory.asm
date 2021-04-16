memset:
    push  rbp
    cld
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosb
    pop   rbp
    ret

GLOBAL memset;

memset64:
    push  rbp
    cld
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosq
    pop   rbp
    ret

GLOBAL memset64;


memset32:
    push  rbp
    cld
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosd
    pop   rbp
    ret

GLOBAL memset32;

memset16:
    push  rbp
    cld
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosw
    pop   rbp
    ret

GLOBAL memset32;

memcpy:
    push  rbp
    cld
    mov   rbp, rsp                   
    ;mov rdi, [rbp+8] // allready set from C call
    ;mov rsi, [rbp+16] // allready set from C call
    mov   rcx, rdx
    rep   movsb
    pop   rbp
    ret

GLOBAL memcpy;

