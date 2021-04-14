memset:
    push  rbp
    mov   rbp, rsp                   
    mov   rax, rsi
    mov   rcx, rdx
    rep stosb
    pop   rbp
    ret

GLOBAL memset;