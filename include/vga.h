#include <stdint.h>

#define VGA_WIDTH 81
#define VGA_HEIGHT 26
#define VGA_MEMORY 0xB8000

void vga_putchar(unsigned char c);
void vga_clear_buffer();
void vga_print(const char *str);
void vga_add_newline();
void vga_shift_buffer();
void vga_shift_buffer();
