#include <vga.h>

void kernel_main(void) {

  vga_clear_buffer();

  vga_print("Hello kernel world!");
}
