.PHONY: all libc kernel qemu clean

all: kernel

libk:
	$(MAKE) -C libc

kernel: libk
	$(MAKE) -C kernel

qemu: kernel
	qemu-system-i386 -kernel kernel/os.kernel

iso: isodir kernel
	cp -v kernel/os.kernel isodir/boot
	grub-mkrescue -o os.iso isodir

qemu-iso: iso
	qemu-system-i386 -cdrom os.iso

isodir:
	mkdir -p isodir/boot/grub
	cp -v grub.cfg isodir/boot/grub

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C kernel clean
	rm -rvf isodir
