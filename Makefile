.PHONY: all libk kernel qemu clean

all: kernel

libk:
	$(MAKE) -C libk

kernel: libk
	$(MAKE) -C kernel

qemu: kernel
	qemu-system-i386 -kernel kernel/os.kernel

clean:
	$(MAKE) -C libk clean
	$(MAKE) -C kernel clean
