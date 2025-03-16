bits    64
;       Selection sort
section .data
n:
        dd      10
mas:
        dd      8, 7, 1, 9, 5, 2, 6, 0, 4, 3
section .text
global  _start
_start:
        mov     rbx, mas
        mov     ecx, [n]
        dec     ecx
        jle     m4
m1:
        push    rcx
        mov     eax, [rbx]
        xor     rdi, rdi
        xor     rsi, rsi
m2:
        inc     rdi
        cmp     eax, [rbx+rdi*4]
        cmovg   eax, [rbx+rdi*4]
        cmovg   rsi, rdi
        loop    m2
        or      rsi, rsi
        je      m3
        mov     edx, [rbx]
        mov     [rbx], eax
        mov     [rbx+rsi*4], edx
m3:
        add     rbx, 4
        pop     rcx
        loop    m1
m4:
        mov     eax, 60
        mov     edi, 0
        syscall
