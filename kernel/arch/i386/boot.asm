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
    align   16

    stack_bottom:
        resb 16384

    stack_top:

    boot_page_directory:
        resb 4096

    boot_page_table1:
        resb 4096

section .multiboot_text:

    global _start
    _start:
       mov edi, boot_page_table1 - 0xC0000000
       mov esi, 0
       mov ecx, 1023
    1:
        cmp esi, kernel_start

        
    
    


section .text
extern kernel_main

    global _start 
    _start:
        mov esp, stack_top

        call kernel_main

    .loop:
        jmp .loop

    global load_page_directory 
    load_page_directory:
        push ebp
        mov ebp, esp 
        
        mov eax, [esp + 8]
        mov cr3, eax

        mov esp, ebp
        pop ebp
        ret

    global enable_paging
    enable_paging:
        push ebp
        mov ebp, esp

        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax
    
        mov esp, ebp
        pop ebp
        ret
