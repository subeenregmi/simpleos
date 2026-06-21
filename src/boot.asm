MB_MAGIC equ 0x1BADB002
MBF_ALIGN equ 1
MBF_MMAP equ 1 << 1
MB_FLAGS equ MBF_ALIGN | MBF_MMAP
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
    align   4
    dd      MB_MAGIC
    dd      MB_FLAGS
    dd      MB_CHECKSUM

section .bss
    align   16

    stack_bottom:
        resb 16384

    stack_top:

section .text
global  _start
extern kernel_main

    _start:
        mov esp, stack_top

        call kernel_main

    .loop:
        jmp .loop


