TC=i686-elf
CC=$(TC)-gcc
AS=nasm

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude -lvga -lstring
ASFLAGS=-felf32
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

OBJ_FILES=build/boot.o build/kernel.o build/vga.o build/string.o
LINKER_SCRIPT=src/linker.ld
OS_FILE=build/os

#CRTBEGIN_OBJ=$($(TC)-gcc $(CFLAGS) -print-file-name=crtbegin.o)
#CRTEND_OBJ=$($(TC)-gcc $(CFLAGS) -print-file-name=crtend.o)


$(OS_FILE): $(OBJ_FILES) $(LINKER_SCRIPT) | build
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(LDFLAGS) $(OBJ_FILES) -lgcc

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $^ -o $@ 

build/%.o: src/%.asm | build
	$(AS) $(ASFLAGS) $^ -o $@

build:
	mkdir -p build

qemu: $(OS_FILE)
	qemu-system-i386 -kernel $(OS_FILE)

clean:
	rm -fv build/*
