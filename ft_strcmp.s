			global 			_ft_strcmp

			section			.text
_ft_strcmp:	xor				rcx, rcx

loop:		movzx			r10, byte [rdi + rcx]
			movzx			r11, byte [rsi + rcx]
			cmp				r11, r10
			jl				greater
			jg				lower
			cmp				[rdi + rcx], byte 0
			je				end
			inc				rcx
			jmp				loop
				
greater:	mov				rax, 1
			ret

lower:		mov				rax, -1
			ret

end:		
			mov				rax, 0
			ret
