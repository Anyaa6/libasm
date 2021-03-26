				global		_ft_read
				extern		___error

            	section		.text
_ft_read:	    mov 	   	 rax, 0x2000003
				syscall
                jc          set_erno
                ret

set_erno:       mov         rdi, rax
                call        ___error
                mov         [rax], rdi
                mov         rax, -1
                ret
