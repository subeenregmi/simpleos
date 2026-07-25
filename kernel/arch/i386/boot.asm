MB_MAGIC equ 0x1BADB002
MB_ALIGN equ 1 << 0
MB_MEMINFO equ 1 << 1
MB_FLAGS equ MB_ALIGN | MB_MEMINFO
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot_header
    align   4
    dd      MB_MAGIC
    dd      MB_FLAGS
    dd      MB_CHECKSUM

section .bss
    alignb 4096

    boot_page_directory:
        resb 4096

    boot_page_table1:
        resb 4096

    stack_bottom:
        resb 16384

    stack_top:

section .multiboot_text
extern _kernel_start, _kernel_end 

    global _start
    _start:
        mov edi, boot_page_table1 - 0xC0000000
        mov esi, 0
        mov ecx, 1023

    .do_kernel_map:
        cmp esi, _kernel_start
        jl .next_pt_entry
        cmp esi, _kernel_end - 0xC0000000
        jge .map_vga_memory

        mov edx, esi
        or edx, 3
        mov dword [edi], edx

    .next_pt_entry:
        add esi, 4096
        add edi, 4
        loop .do_kernel_map

    .map_vga_memory:
        mov dword [boot_page_table1 - 0xC0000000 + 1023 * 4], 0x000B8000 | 0x3
        
        mov dword [boot_page_directory - 0xC0000000], boot_page_table1 - 0xC0000000 + 0x3
        mov dword [boot_page_directory - 0xC0000000 + 768 * 4], boot_page_table1 - 0xC0000000 + 0x3

        mov ecx, boot_page_directory - 0xC0000000
        mov cr3, ecx

        mov ecx, cr0
        or ecx, 0x80010000
        mov cr0, ecx

        lea ecx, [higher_half_kernel] 
        jmp ecx 

section .text
extern kernel_main

    global higher_half_kernel 
    higher_half_kernel:

        mov dword [boot_page_directory], 0

        mov ecx, cr3
        mov cr3, ecx

        mov esp, stack_top

        call kernel_main

    .loop:
        jmp .loop