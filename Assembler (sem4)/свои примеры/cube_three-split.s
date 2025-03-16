bits 64

; calculate a^3 = a * a
; by algorithm of splitting into three parts:

; a -> a*a = lowbits + highbits
; lowbits(a^2) -> lowbits(a^2) * a = lowbits(a^3) + middle-lowbits(a^3)
; highbits(a^2) -> highbits(a^2) * a = middle-highbits(a^3) + highbits(a^3)
; middlebits(a^3) = middle-lowbits + middle-highbits

; a^3 = lowbits(a^3) + middlebits(a^3) + highbits(a^3)

section .data
	num: dw 300
	res: dq 0

section .text
	global _start

_start:
	; a * a
	mov ax, word [num]
	xor dx, dx
	imul ax
	; save high bits for later
	mov bx, dx

	; so:
	; ax - lowbits(a^2)
	; bx - highbits(a^2)

	; lowbits(a) * a
	xor dx, dx
	imul word[num]
	; save highbits(lowbits_a^2) = middlebits(a^3) (incorrect for now)
	mov cx, dx

	; so:
	; ax - lowbits(a^3)
	; cx - middle-lowbits(a^3)
	; bx - highbits(a^2)
	xchg ax, bx
	; bx - lowbits(a^3)
	; cx - middle-lowbits(a^3)
	; ax - highbits(a^2)

	; calculate high bits
	xor dx, dx
	imul word[num]

	; so:
	; bx - lowbits(a^3)
	; cx - middle-lowbits(a^3)
	; ax - middle-highbits(a^3)
	; dx - highbits(a^3)

	; calculate middle bits = sum of two parts
	add ax, cx
	seto cl
	movsx cx, cl
	add ax, cx

	; in the end: a^3 = edx:eax:ebx (48 bits total)
	shl eax, 16
	movsx [res], eax
	; shr eax, 16
	or res, ebx

; idk why but rax has correct answer and res doesnt if it's more than 32bits
; like 300^3 = 27mil is ok, but 2000^3 = 8bil isnt
	shl edx, 32
	or res, edx
	; shr edx, 32

	; exit the program
	mov rax, 60
	xor rdi, rdi
	syscall
