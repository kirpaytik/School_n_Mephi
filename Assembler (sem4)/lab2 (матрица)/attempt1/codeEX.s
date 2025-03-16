bits 64

; matrix' lines Shell sort by line's max element

%ifdef SORT_ORDER
	%if SORT_ORDER = "ASCEND"
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
	maxes:dd 0,  0,  0,  0,  0,  0

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
; r10 - Shell sort's gap

; also rdi and rsi - registers with arguments for funcs
; and rax is used for returning values from funcs

_start:
	mov rbx, matr

calculate_maxes:
	movzx ecx, byte[n]
	xor rdi, rdi
calculate_maxes_loop:
	; matr[dil] = rbx + dil*m*4
	movzx rax, dil
	movzx dx, byte[m]
	mul dx
	shl eax, 2
	add rax, rbx

	push rdi
	mov rdi, rax
	call search_max
	pop rdi

	mov esi, eax
	; maxes[dil] = maxes + dil*4
	movzx rax, dil
	shl ax, 2
	add rax, maxes
	mov [rax], esi

	inc dil
	loop calculate_maxes_loop

sort_start:
	movzx r10, byte[n] ; Shell sort's gap
	shr r10, 1 ; gap /= 2
	je exit_program ; n < 2 <=> initial gap=0
	xor rdi, rdi ; index of line to insert somewhere

gap_loop:
	movzx ecx, byte[n]
	sub cl, r10b ; (n - gap) is cycle counter number
	mov dil, r10b
	dec dil ; cuz it's being inc'd in m1 right away

m1:
	inc dil

	; save matr[rdi] in buf
	; mov rax, rbx+rdi*4*m (= matr[rdi])
;	movzx rax, dil
;	shl ax, 2 ; equal to multiplying by 4
;	movzx rdx, byte[m]
;	mul rdx
;	add rax, rbx
	; mov [buf], [rax]
	movzx rsi, dil
	push rdi
	movzx rdi, byte[m] ; len = last_index + 1 - for buf in maxes
	call mov_line
	pop rdi

	mov sil, dil ; index of line to compare with buf

m2:
	sub sil, r10b
	jl m3

	; checking if it's possible to move buf into matr[rsi]

	; mov r8, rbx+rsi*4*m (= matr[rsi])
	movzx rax, sil
	shl ax, 2 ; equal to multiplying by 4
	movzx rdx, byte[m]
	mul rdx
	add rax, rbx
	mov r8, rax

	; cmp buf, [rbx+rsi*4*m]
	;push rdi
	;push rsi
	;mov rdi, buf
	;mov rsi, r8
	call cmp_lines
	;pop rsi
	;pop rdi
	or al, al
	jnz m3

	; allowed to move buf into matr[rsi] =>
	; move matr[rsi] by one to the right

	; mov r9, 4*m*gap + rbx+rsi*4*m (= matr[rsi+gap])
	movzx rax, byte[m]
	shl ax, 2 ; equal to multiplying by 4
	mul r10 ; gap
	add rax, r8
	mov r9, rax

	; mov [rbx+(rsi+gap)*4*m], [rbx+rsi*4*m]
	push rdi
;	push rsi
;	mov rdi, r9
;	mov rsi, r8
	movzx rdi, sil
	add dil, r10b ; !!!!! di is better but dil is enough
	call mov_line
;	pop rsi
	pop rdi

	jmp m2

m3:
	; actual move of buf into its corresponding slot
	; mov [rbx+(rsi+gap)*4*m], [buf]
;	add sil, r10b ; gap
;	movzx rax, sil
;	shl ax, 2 ; equal to multiplying by 4
;	movzx rdx, byte[m]
;	mul rdx
;	add rax, rbx

	push rdi
	movzx rdi, sil
	add dil, r10b ; !!!!! di is better but dil is enough
	push rsi
	movzx rsi, byte[m] ; len = last_index + 1
	call mov_line
	pop rsi
	pop rdi

	; loop m1 ; error: short jump is out of range ; byte data exceeds bounds [-w+number-overflow]
	dec ecx
	jg m1

gap_loop_end:
	shr r10b, 1 ; gap /= 2
	jnz gap_loop

exit_program:
	mov rax, 60
	xor rdi, rdi
	syscall


; funcs

; cmp matr[rdi], matr[rsi]
cmp_lines:
	; create stack frame - not needed lol
	; push rbp
	; mov rbp, rsp
	; sub rsp, ... ; memory "allocation"

	;call search_max
	;mov edx, eax
	;xchg rdi, rsi
	;call search_max
	;xchg rsi, rdi ; not needed cuz it's just for fun's arguments in this case

	; matr[rdi] = maxes + rdi*4
	movzx rax, dil
	shl ax, 2
	add rax, maxes
	movzx rdx, sil
	shl dx, 2
	add rdx, maxes

	mov r14d, dword[rax]
	mov r15d, dword[rdx]
	cmp r14d, r15d
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

mov_line_maxes:
	; maxes[dil] = maxes + dil * 4
	movzx rax, dil
	shl ax, 2
	add rax, maxes
	movzx rdx, sil
	shl dx, 2
	add rdx, maxes

	mov r13d, dword[rdx]
	mov [rax], r13d

	; rdi - first line (dest) index
	; rsi - second line (src) index
	; ecx - loop counter + index to elements to swap

	; calculate matr[rdi] = rbx + rdi * 4 * m
	movzx rax, dil
	shl ax, 2
	movzx r12, byte[m]
	mul r12
	add rax, rbx

	mov r13, rax
	movzx rax, sil
	shl ax, 2
	mul r12
	add rax, rbx

	movzx ecx, byte[m]
	test ecx, ecx
	jz m_movline_exit
	dec cl ; so cl is len - 1

m_movline_1:
	mov ecx, ecx ; so bits 32-63 in rcx are set to 0
	mov r12d, dword[rax+rcx*4]
	mov dword[r13+rcx*4], r12d
	; loop m_movline_1 ; doesnt consider cl == 0
	dec cl
	jge m_movline_1

	; or instead of cycle just:
	; rep movsd



m_movline_exit:
	pop rcx
	ret
