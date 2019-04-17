OBJECTS = ./dist/loader.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: loader.o kernel.elf os.iso

loader.o: loader.s
	 mkdir -p ./dist
	 nasm -f elf32 loader.s -o ./dist/loader.o

kernel.elf: $(OBJECTS)
	mkdir -p ./dist
	ld $(LDFLAGS) $(OBJECTS) -o ./dist/kernel.elf

os.iso: kernel.elf
	mkdir -p ./dist/iso/boot/grub
	cp ./dist/kernel.elf ./dist/iso/boot/kernel.elf
	cp grub.cfg ./dist/iso/boot/grub
	grub-mkrescue -o ./dist/os.iso ./dist/iso

run: os.iso
	mkdir -p ./dist
	qemu-system-x86_64 -hda ./dist/os.iso

%.o: %.c
	 $(CC) $(CFLAGS)  $< -o ./dist/$@

%.o: %.s
	 $(AS) $(ASFLAGS) $< -o ./dist/$@

clean:
	rm -rf ./dist
	mkdir -p ./dist

