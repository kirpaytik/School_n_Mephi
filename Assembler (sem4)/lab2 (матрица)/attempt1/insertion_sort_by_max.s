bits 64

; matrix' lines Shell sort by line's max element

%ifdef SORT_ORDER
	%if SORT_ORDER = ASCEND
		%define CMP_INSTR setge
	%else
		%define CMP_INSTR setle
	%endif
%else
	%define CMP_INSTR setge
%endif

section .data
	n: db 5
	m: db 5
	matr: dd 12, 7,  3,  9,  15
		  dd 5,  11, 8,  2,  14
		  dd 1,  10, 6,  13, 4
		  dd 21, 25, 22, 23, 24
		  dd 18, 17, 16, 20, 19

	buf:  dd 0,  0,  0,  0,  0

section .text
	global _start

; usage of registers throughout the program:
; rax - empty, is used for arithmetic operations
; rbx - ptr to matr
; ecx - loop counter
; rdx - empty, is used for containing temporary values
; 		(which cannot be accessed from memory directly)
; rdi - index of line to insert somewhere
; 		(which is stored in buf)
; rsi - index of line to compare with buf
; r8  - temporary adresses
; r9  - temporary adresses

; also rdi and rsi - registers with arguments for funcs
; and rax is used for returning values from funcs

_start:
	mov rbx, matr
	movzx ecx, byte[n]
	dec cl
	jle exit_program ; n < 2
	xor dil, dil ; index of line to insert somewhere

m1:
	inc dil

	; save matr[rdi] in buf
	; mov rax, rbx+rdi*4*m (= matr[rdi])
	movzx rax, dil
	shl rax, 2 ; equal to multiplying by 4
	movzx rdx, byte[m]
	mul rdx
	add rax, rbx
	; mov [buf], [rax]
	push rdi
	mov rdi, buf
	mov rsi, rax
	call mov_line
	pop rdi

	mov sil, dil ; index of line to compare with buf

m2:
	dec sil
	jl m3

	; checking if it's possible to move buf into matr[rsi]

	; mov r8, rbx+rsi*4*m (= matr[rsi])
	movzx rax, sil
	shl rax, 2 ; equal to multiplying by 4
	movzx rdx, byte[m]
	mul rdx
	add rax, rbx
	mov r8, rax

	; cmp buf, [rbx+rsi*4*m]
	push rdi
	push rsi
	mov rdi, buf
	mov rsi, r8
	call cmp_lines
	pop rsi
	pop rdi
	or al, al
	jnz m3

	; allowed to move buf into matr[rsi] =>
	; move matr[rsi] by one to the right

	; mov r9, rbx+(rsi+1)*4*m (= matr[rsi+1])
	movzx rax, byte[m]
	shl rax, 2 ; equal to multiplying by 4
	add rax, r8
	mov r9, rax

	; mov [rbx+rsi*4*m+4*m], [rbx+rsi*4*m]
	push rdi
	push rsi
	mov rdi, r9
	mov rsi, r8
	call mov_line
	pop rsi
	pop rdi

	jmp m2

m3:
	; actual move of buf into its corresponding slot
	; mov [rbx+rsi*4*m+4], [buf]
	inc sil
	movzx rax, sil
	shl rax, 2 ; equal to multiplying by 4
	movzx rdx, byte[m]
	mul rdx
	add rax, rbx

	push rdi
	mov rdi, rax
	push rsi
	mov rsi, buf
	call mov_line
	pop rsi
	pop rdi

	; loop m1 ; error: short jump is out of range ; byte data exceeds bounds [-w+number-overflow]
	dec ecx
	jg m1

exit_program:
	mov rax, 60
	xor rdi, rdi
	syscall


; funcs

; cmp [rdi], [rsi]
cmp_lines:
	; create stack frame - not needed lol
	; push rbp
	; mov rbp, rsp
	; sub rsp, ... ; memory "allocation"

	call search_max
	mov edx, eax
	xchg rdi, rsi
	call search_max
	xchg rsi, rdi ; not needed cuz it's just for fun's arguments in this case

	cmp edx, eax
	CMP_INSTR al ; setge for ASCEND, setle for DESCEND
	movzx rax, al

	; delete stack frame
	; mov rsp, rbp
	; pop rbp
	; or just 'leave'
	ret


search_max:
	push rcx

	; rdi - ptr to mas
	; ecx - loop counter + index to element
	; eax - max element
	xor eax, eax
	movzx ecx, byte[m]
	test cl, cl
	jz m_search_exit ; m == 0

	mov eax, dword[rdi]
	dec cl ; so ecx is len-1
	jle m_search_exit ; m == 1

m_search_1:
	mov ecx, ecx ; so bits 32-63 in rcx are set to 0
	cmp eax, [rdi+rcx*4]
	cmovl eax, [rdi+rcx*4]
	; loop m_search_1 ; doesnt consider cl = 0
	dec cl
	jg m_search_1

m_search_exit:
	pop rcx
	ret


; mov [rdi], [rsi]
mov_line:
	push rcx

	; rdi - first line (dest)
	; rsi - second line (src)
	; ecx - loop counter + index to elements to swap
	movzx ecx, byte[m]
	test ecx, ecx
	jz m_movline_exit
	dec cl ; so cl is len - 1

m_movline_1:
	mov ecx, ecx ; so bits 32-63 in rcx are set to 0
	mov edx, dword[rsi+rcx*4]
	mov dword[rdi+rcx*4], edx
	; loop m_movline_1 ; doesnt consider cl == 0
	dec cl
	jge m_movline_1

	; or instead of cycle just:
	; rep movsd

m_movline_exit:
	pop rcx
	ret
