#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <vga.h>

volatile uint16_t *vga_buffer = (uint16_t *)VGA_MEMORY;
size_t vga_cursor_x = 0;
size_t vga_cursor_y = 0;

void vga_clear_line(size_t y) {
  for (size_t i = 0; i < VGA_WIDTH; i++) {
    vga_buffer[y * VGA_WIDTH + i] = 0;
  }
}

void vga_add_newline() {
  vga_cursor_x = 0;
  vga_cursor_y++;

  if (vga_cursor_y == VGA_HEIGHT) {
    vga_shift_buffer();
    vga_cursor_y--;
  }
}

void vga_shift_buffer() {
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
    }
  }
  vga_clear_line(VGA_HEIGHT - 1);
}

void vga_inc_cursor() {
  vga_cursor_x++;

  if (vga_cursor_x > VGA_WIDTH) {
    vga_cursor_x %= VGA_WIDTH;
    if (vga_cursor_y == VGA_HEIGHT - 1) {
      vga_shift_buffer();
    } else {
      vga_cursor_y++;
    }
  }
}

void vga_putchar(unsigned char c) {
  uint32_t bright_white = 0xF;
  if (c == '\n') {
    vga_add_newline();
    return;
  }

  vga_buffer[vga_cursor_x + vga_cursor_y * VGA_WIDTH] = c | bright_white << 8;
  vga_inc_cursor();
}

void vga_clear_buffer() {
  for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    vga_buffer[i] = 0;
  }
}

void vga_print(const char *str) {
  for (size_t i = 0; i < strlen(str); i++) {
    vga_putchar(str[i]);
  }
}
