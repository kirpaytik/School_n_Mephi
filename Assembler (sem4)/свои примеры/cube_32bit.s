bits 64

section .data
	num: dw 300
	res: dq 0

section .text
	global _start

_start:
	; firstly, calculate a^3
	; a * a (result in edx:eax)
	xor edx, edx
	mov eax, dword[num]
	imul eax
	; (a^2) result in rax
	shl rdx, 32
	movsx rax, eax
	or rax, rdx
	; a^2 * a (result in rdx:rax)
	; (but result will be only 96 bits (cuz 32*3), so high 16 in edx is 0)
	movsx rbx, dword[num]
	imul rbx

	; check if a^3 can be stored in just rax
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

exit_program:
	mov rax, 60
	xor rdi, rdi
	syscall
