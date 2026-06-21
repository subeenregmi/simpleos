TC=i686-elf
CC=$(TC)-gcc
AS=nasm

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude -I../libk/include
ASFLAGS=-felf32
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

OBJS=\
	arch/i386/boot.o \
	kernel/kernel.o \
	arch/i386/vga.o
LINKER_SCRIPT=arch/i386/linker.ld
LIBK=../libk/libk.a
OS=os.kernel

all: $(OS)
$(OS): $(OBJS) $(LINKER_SCRIPT)
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(LDFLAGS) $(OBJS) $(LIBK) -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

%.o: %.asm 
	$(AS) $(ASFLAGS) $^ -o $@

qemu: $(OS_FILE)
	qemu-system-i386 -kernel $(OS_FILE)

clean:
	rm -fv $(OBJS) $(OS)
