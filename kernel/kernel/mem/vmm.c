#include <kernel/mm/vmm.h>
#include <stdint.h>

void init_page_directory(struct pde *pd) {
  for (int i = 0; i < PD_ENTRIES; i++) {
    pd[i].flags = PDE_WRITABLE | PDE_USER;
  }
}

void init_identity_page_table(struct pte *pt) {
  for (int i = 0; i < PT_ENTRIES; i++) {
    pt[i].paddr = i;
    pt[i].flags = PTE_WRITABLE | PTE_USER | PTE_PRESENT;
  }
}
