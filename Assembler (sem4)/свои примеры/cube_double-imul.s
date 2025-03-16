bits 64

section .data
	num: dw 300
	res: dq 0

section .text
	global _start

_start:
	; a * a (result in dx:ax)
	xor dx, dx
	mov ax, word[num]
	imul ax

	; (a^2) result in eax
	shl edx, 16
	movsx eax, ax
	or eax, edx

	; a^2 * a (result in edx:eax)
	; (but result will be only 48 bits (cuz 16*3), so high 16 in edx is 0)
	movsx ebx, word[num]
	imul ebx

	; (a^3) result in rax
	shl rdx, 32
	; mov rax, eax - ругается здесб, ьлин, ачто...
	movsx rax, eax
	or rax, rdx

	; save result in res
	mov qword[res], rax
; idk why but rax has correct answer and res doesnt if it's more than 32bits
; like 300^3 = 27mil is ok, but 2000^3 = 8bil isnt

	; exit the program
	mov rax, 60
	xor rdi, rdi
	syscall
