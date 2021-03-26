			global 			_ft_strdup
			extern			_malloc
			extern			_ft_strlen
			extern			_ft_strcpy

			section			.text
_ft_strdup:	
			call			_ft_strlen
			push			rdi
			add				rax, 1
			mov				rdi, rax
			call			_malloc
			pop				rsi
			mov				rdi, rax
			call			_ft_strcpy
			ret
