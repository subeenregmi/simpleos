#include <kernel/mm/vmm.h>
#include <kernel/vga.h>
#include <stdint.h>

void kernel_main(void) {

  vga_clear_buffer();

  vga_print("Hello kernel world!");
}
