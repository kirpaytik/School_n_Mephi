bits    64
;       Shaker sort
section .data
n:
        dd      10
mas:
        dd      8, 7, 1, 9, 5, 2, 6, 0, 4, 3
section .text
global  _start
_start:
        mov     rcx, mas
        mov     edi, [n]
        dec     edi
        jle     m5
        shl     rdi, 2
        add     rdi, rcx
m1:
        mov     rsi, rcx
        cmp     rsi, rdi
        jge     m5
        mov     rbx, rsi
        mov     eax, [rbx]
m2:
        cmp     rbx, rdi
        jg      m3
        add     rbx, 4
        mov     edx, [rbx]
        cmp     eax, edx
        cmovl   eax, edx
        jle     m2
        lea     rcx, [rbx-4]
        mov     [rbx], eax
        mov     [rbx-4], edx
        jmp     m2
m3:
        mov     rdi, rcx
        cmp     rsi, rdi
        jge     m5
        mov     rbx, rdi
        mov     eax, [rbx]
m4:
        cmp     rbx, rsi
        jle     m1
        sub     rbx, 4
        mov     edx, [rbx]
        cmp     eax, edx
        cmovg   eax, edx
        jge     m4
        lea     rcx, [rbx+4]
        mov     [rbx], eax
        mov     [rbx+4], edx
        jmp     m4
m5:
        mov     eax, 60
        mov     edi, 0
        syscall
