bits    64
;       Bubble sort
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
        jle     m5
m1:
        push    rcx
        mov     eax, [rbx]
        xor     rdi, rdi
m2:
        inc     edi
        mov     edx, [rbx+rdi*4]
        cmp     eax, edx
        jg      m3
        mov     eax, edx
        jmp     m4
m3:
        mov     [rbx+rdi*4-4], edx
        mov     [rbx+rdi*4], eax
m4:
        loop    m2
        pop     rcx
        loop    m1
m5:
        mov     eax, 60
        mov     edi, 0
        syscall
