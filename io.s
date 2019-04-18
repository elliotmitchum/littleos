FB equ 0x00B8000

global out

out:
	 
	 ; Store second arg (data) in EDX.
	 mov edx, [esp + 8]

	 ; Store first arg (offset) in EBX.
	 mov ebx, [esp + 4]

	 ; Move data to buffers.
	 mov [FB + ebx], edx

	 ret

