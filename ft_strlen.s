; nasm -fmacho64 ft_strlen.s && gcc ft_strlen.o main.c && ./a.out
	        
			global    _ft_strlen

            section		.text
_ft_strlen:	xor			rcx, rcx
loops:		cmp			[rdi + rcx], byte 0
			je			exit
			inc			rcx
			jmp			loops

exit:		mov     	rax, rcx
    		ret
