bits    64
;       Search max
section .data
n:
        dd      10
mas:
        dd      6, 5, 1, 0, 9, 2, 3, 8, 4, 7
max:
        dd      0
section .text
global  _start
_start:
        mov     rbx, mas
        mov     ecx, [n]
        or      ecx, ecx
        jle     m3
        mov     eax, [rbx]
        xor     rdi, rdi
        dec     ecx
        jecxz   m2
m1:
        inc     rdi
        cmp     eax, [rbx+rdi*4]
        cmovl   eax, [rbx+rdi*4]
        loop    m1
m2:
        mov     [max], eax
m3:
        mov     eax, 60
        mov     edi, 0
        syscall
