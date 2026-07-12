#include <kernel/mm/vmm.h>
#include <stdint.h>

void init_page_directory(uint32_t *pd) {
  for (int i = 0; i < PD_ENTRIES; i++) {
    pd[i] = PDE_WRITABLE | PDE_USER;
  }
}

void init_identity_page_table(uint32_t *pt) {
  for (int i = 0; i < PT_ENTRIES; i++) {
    pt[i] = (i * 0x1000) | PTE_WRITABLE | PTE_USER | PTE_PRESENT;
  }
}
