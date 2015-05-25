intpow:
	push	rbp
	mov	rbp, rsp
	mov	rax, 1
.powloop:
	imul	rax, rsi
	dec	rdi
	cmp	rdi, 0
	jg	.powloop
	mov	rsp, rbp
	pop	rbp
	ret

array_oob_error:
	mov rdi, array_oob_str
	mov al, 0
	and rsp, 0xfffffffffffffff0
	call printf
	mov rax, 60
	syscall
