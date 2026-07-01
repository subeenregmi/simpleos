TC=i686-elf
CC=$(TC)-gcc
AS=nasm

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude -I../libc/include
ASFLAGS=-felf32
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

CRTI_OBJ=arch/i386/crti.o
CRTN_OBJ=arch/i386/crtn.o
OBJS=\
	arch/i386/boot.o \
	kernel/kernel.o \
	arch/i386/vga.o 

INTERNAL_OBJS=$(OBJS) $(CRTI_OBJ) $(CRTN_OBJ)

CRTBEGIN_OBJ=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

LINKER_SCRIPT=arch/i386/linker.ld
LIBK=../libc/libk.a
OS=os.kernel

SYSROOT_DIR=../sysroot

OBJS_LINK_LIST=\
			   $(CRTI_OBJ) \
			   $(CRTBEGIN_OBJ) \
			   $(OBJS) \
			   $(LIBK) \
			   $(CRTEND_OBJ) \
			   $(CRTN_OBJ) 

all: $(OS)

$(OS): $(INTERNAL_OBJS) $(LINKER_SCRIPT)
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(LDFLAGS) $(OBJS_LINK_LIST) -lgcc
	grub-file --is-x86-multiboot $(OS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

%.o: %.asm 
	$(AS) $(ASFLAGS) $^ -o $@

install: install-headers install-kernel

install-headers:
	mkdir -vp $(SYSROOT_DIR)/usr/include/
	cp -R --preserve=timestamps ./include/* $(SYSROOT_DIR)/usr/include/

install-kernel: $(OS)
	mkdir -vp $(SYSROOT_DIR)/boot/
	cp $(OS) $(SYSROOT_DIR)/boot/

clean:
	rm -fv $(INTERNAL_OBJS) 
	rm -fv $(OS)
