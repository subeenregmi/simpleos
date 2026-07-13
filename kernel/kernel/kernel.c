#include <kernel/mm/vmm.h>
#include <kernel/vga.h>
#include <stdint.h>

struct pde page_directory[PD_ENTRIES] __attribute__((aligned(4096)));
struct pte first_page_table[PT_ENTRIES] __attribute__((aligned(4096)));

extern void load_page_directory(struct pde *);
extern void enable_paging();

void kernel_main(void) {

  init_page_directory(page_directory);
  init_identity_page_table(first_page_table);

  page_directory[0].pte_addr = (unsigned int)&first_page_table >> 12;
  page_directory[0].flags = PDE_PRESENT | PDE_USER;

  load_page_directory(page_directory);
  enable_paging();

  vga_clear_buffer();

  vga_print("Hello kernel world!");
}
