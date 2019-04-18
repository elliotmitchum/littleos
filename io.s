FB equ 0x00B8000

global out

out:

	 mov edx, [esp + 4]
	 mov [FB], edx
	 ret

