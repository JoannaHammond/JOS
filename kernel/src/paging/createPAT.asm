[bits 64]
CreatePAT:  
wbinvd

mov eax, 0x00010406
mov edx, 0x00010406
mov ecx, 0x277
wrmsr

wbinvd

;pop rdi
;mov rax, 0x08
;push rax
;push rdi
;retfq
ret


GLOBAL CreatePAT