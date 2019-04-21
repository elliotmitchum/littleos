FB equ 0x00B8000

global out

; Send a byte to frame buffer.
out:
	 
	 ; Store second arg (data) in EDX.
	 mov edx, [esp + 8]

	 ; Store first arg (offset) in EBX.
	 mov ebx, [esp + 4]

	 ; Move data to buffers.
	 mov [FB + ebx], edx

	 ret

global outb

; Send a byte to IO port.
; Return address is stored in ESP.
outb:
	 
	 ; Store second arg (data) in EDX.
	 mov al, [esp + 8]

	 ; Store first arg (port address) in DX.
	 mov dx, [esp + 4]

	 ; Move data to port address.
	 out dx, al
	 
	 ; Clear stack.
	 ret

global inb

; Receive a byte from IO port.
; Return address is stored in ESP.
inb:
	 
	 ; Move first argument (port address) to DX.
	 mov dx, [esp + 4]

	 ; Receive byte from port address.
	 in al, dx

	 ; Clear stack.
	 ret

