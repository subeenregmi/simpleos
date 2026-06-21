TC=i686-elf
CC=$(TC)-gcc
AR=$(TC)-ar
AS=nasm

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude

OBJS=string/strlen.o

LIBK=libk.a

all: $(LIBK)

$(LIBK): $(OBJS) 
	$(AR) -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

clean:
	rm -fv $(OBJS) $(LIBK)
