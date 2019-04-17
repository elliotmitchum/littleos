; x86 boot process:
; 1. CPU executes BIOS instructions.
; 2. After completion, BIOS searches for bootable device, bootable device must contain magic number.
; 3. BIOS loads and executes bootloader.
; 4. Bootloader loads and passes control to kernel.

global loader						; The entry symbol for ELF.

MAGIC_NUMBER equ 0x1BADB002	; Define the magic number constant, allows. Multiboot to reconize bootable device.
FLAGS equ 0x0						; Set multiboot flags to zero.
CHECKSUM equ -MAGIC_NUMBER  	; Calculate the checksum (magic number + checksum + flags should equal 0).

FB equ 0x000B8000

section .text						; Start of the text (code) section.
									   ; Write Multiboot header.
	align 4							; The code must be 4 byte aligned as per Multiboot spec.
	dd MAGIC_NUMBER				; Write the magic number to the machine code for BIOS to identify boot device.
	dd FLAGS							; Write flags.
	dd CHECKSUM						; Write checksum.

loader:								; Loader label (defined as entry point in linker script).
	mov eax, 0xCAFEBABE			; Place the number 0xCAFEBABE in the register eax.
	mov [FB], dword 0xF045

.loop:
	jmp .loop						; Loop forever.

