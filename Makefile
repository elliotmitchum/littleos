OBJECTS = loader.o kmain.o io.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: loader.o kernel.elf os.iso

loader.o: loader.s
	 nasm -f elf32 loader.s -o loader.o

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	mkdir -p ./iso/boot/grub
	cp kernel.elf ./iso/boot/kernel.elf
	cp grub.cfg ./iso/boot/grub
	grub-mkrescue -o ./iso/os.iso iso

run: os.iso
	qemu-system-x86_64 -hda ./iso/os.iso

%.o: %.c
	 $(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	 $(AS) $(ASFLAGS) $< -o $@

clean:
	 rm -rf *.o kernel.elf iso
