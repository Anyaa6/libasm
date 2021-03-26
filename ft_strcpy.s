			global 			_ft_strcpy

			section			.text
_ft_strcpy:	xor				rcx, rcx
			mov				rax, rsi

loop:		mov				r10, [rsi + rcx]
			mov				[rdi + rcx], r10
			cmp				[rdi + rcx], byte 0
			je				exit
			inc				rcx
			jmp				loop
			ret

exit:		ret	
