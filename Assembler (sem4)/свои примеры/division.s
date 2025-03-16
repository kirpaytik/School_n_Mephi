bits 64

; division test program

section .data
	num: dd -5536
	den: dw 2
	quotient: dw 0
	remainder: dw 0

section .text
	global _start

_start:
	; num -> dx:ax, den -> bx
	mov ax, word[num]
	mov dx, word[num + 2]
	mov bx, word[den]

	; if dx >= bx then result is bigger than 16 bits
	; and cannot be written in ax
	; not correct if dx=-1 and bx=1
	mov cx, dx ; save value
	test dx, dx
	jns check_overflow
	neg dx
check_overflow:
	cmp dx, bx
	ja exit
	mov dx, cx ; restore its original value

	idiv bx

	mov [quotient], ax
	mov [remainder], dx

exit:
	; exit the program
	mov rax, 60
	xor rdi, rdi
	syscall
