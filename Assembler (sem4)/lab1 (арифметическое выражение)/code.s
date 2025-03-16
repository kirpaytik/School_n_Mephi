bits 64

; ( (a+b)^2 - (c-d)^2 ) / ( a + e^3 - c )

section .data
	a: dw 2
	b: dw 3
	c: dd 4
	d: dd 5
	e: dd 2
	res: dq 0

section .text
	global _start

_start:
	; firstly, calculate e^3
	; e * e (result in edx:eax)
	xor edx, edx
	mov eax, dword[e]
	imul eax
	; (e^2) result in rax
	shl rdx, 32
	movsx rax, eax
	or rax, rdx
	; e^2 * e (result in rdx:rax)
	; (but result will be only 96 bits (cuz 32*3), so high 16 in edx is 0)
	movsx rbx, dword[e]
	imul rbx

	; check if e^3 can be stored in just rax
	; rdx should be 0 or -1
	test rdx, rdx
	jz continue_m1
	cmp rdx, -1
	jz continue_m1
	jmp exit_program
continue_m1:
	; the highest bits of rax and rdx should be equal
	mov rbx, rax
	mov rcx, rdx
	shr rbx, 32 ; cuz i cant do: test rbx, 0x8000000000000000
	shr rcx, 32
	test ebx, 0x80000000
	test ecx, 0x80000000
	cmp ebx, ecx
	jnz exit_program

	; calculate full denominator
	movsx rbx, word[a]
	add rax, rbx
	jo exit_program

	movsx rbx, dword[c]
	sub rax, rbx
	jo exit_program

	; check for division by zero
	or rax, rax
	jz exit_program
	mov rdi, rax

	; calculate nominator
	; (a + b)^2
	mov ax, word[a]
	add ax, word[b]
	jo exit_program
	imul ax
	; result in dx:ax => save in eax
	movzx eax, ax
	shl edx, 16
	or eax, edx
	mov ebx, eax
	; (c - d)^2
	mov eax, dword[c]
	sub eax, dword[d]
	jo exit_program
	imul eax
	; result in edx:eax => save in rax
	movsx rax, eax
	shl rdx, 32
	or rax, rdx
	; nominator
	sub rbx, rax
	jo exit_program

	; nominator / denominator
	mov rax, rbx
	cqo
	idiv rdi
	mov [res], rax

exit_program:
	mov rax, 60
	xor rdi, rdi
	syscall
