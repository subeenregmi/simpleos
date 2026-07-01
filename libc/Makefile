MAKEFLAGS=--warn-undefined-variables

TC=i686-elf
CC=$(TC)-gcc
AR=$(TC)-ar
AS=nasm

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

OBJS=string/strlen.o

LIBK=libk.a

SYSROOT_DIR=../sysroot

all: $(LIBK)

$(LIBK): $(OBJS) 
	$(AR) -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

clean:
	rm -fv $(OBJS) $(LIBK)

install: install-headers install-libs

install-headers:
	mkdir -vp $(SYSROOT_DIR)/usr/include/
	cp -R --preserve=timestamps ./include/* $(SYSROOT_DIR)/usr/include/

install-libs: $(LIBK)
	mkdir -vp $(SYSROOT_DIR)/usr/lib/
	cp $(LIBK) $(SYSROOT_DIR)/usr/lib
