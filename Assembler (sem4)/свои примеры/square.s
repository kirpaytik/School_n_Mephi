bits 64

; calculate a^2 = a * a

section .data
	num: dw 300
	res: dd 0

section .text
	global _start

_start:
	; num * num
	mov ax, word [num]
	imul ax
	; result in dx:ax => save in eax
	movzx eax, ax
	shl edx, 16
	or eax, edx
	; save in res
	mov dword[res], eax

	; exit the program
	mov rax, 60
	xor rdi, rdi
	syscall
