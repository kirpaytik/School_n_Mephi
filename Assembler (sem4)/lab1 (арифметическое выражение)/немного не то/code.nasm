section .data
	a: .word 5
	b: .word 3
	c: .dword 8
	d: .dword 2
	e: .dword 2
	result: 0
	error_code: .word 0

	sys_exit 60

section .text
	.global _start

_start:
	; (a + b) ^ 2
	movq a, %ax
	addq b, %eax
	imulq %rax, %rax

	; (c - d) ^ 2
	movq c, %ebx
	subq d, %rbx
	imulq %rbx, %rbx

	jo error_occured

	; numerator
	subq %rbx, %rax

	; (e^3 + a - c)
	movq e, %ebx
	imulq %rbx, %rbx
	imulq e, %rbx
	jo error_occured
	adq a, %rbx
	jo error_occured
	subq c, %rbx
	jo error_occured

	cmpq $0, %rbx
	je error_occured

	xor %rdx, %rdx
	cqto
	idivl %rbx
	movq %rax, result(%rip)
	movq &0, error_code
	jmp exit_program

error_occured:
	movq %1, error_code
	jmp exit_program

exit_program:
	movq sys_exit, %rax
	xorq error_code, %rdi
	syscall
