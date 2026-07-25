#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xC03FF000

void vga_putchar(unsigned char c);
void vga_clear_buffer();
void vga_print(const char *str);
void vga_add_newline();
void vga_shift_buffer();
