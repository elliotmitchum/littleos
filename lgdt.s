global lgdt_load

; Load GDT.
lgdt_load:
  mov eax, [esp + 4]
  lgdt [eax]
  ret

  ; Jump to code segment.
  jmp 0x08: .lgdt_reload

; Load GDT segment.
.lgdt_reload:
  mov ax, 0x10
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov gs, ax
  mov fs, ax
  ret

