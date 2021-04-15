memset:
    push  rbp
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosb
    pop   rbp
    ret

GLOBAL memset;


memset32:
    push  rbp
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosd
    pop   rbp
    ret

GLOBAL memset32;

memset16:
    push  rbp
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosw
    pop   rbp
    ret

GLOBAL memset32;