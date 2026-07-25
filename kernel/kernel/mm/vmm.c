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

void map_page(struct pde *pd, struct vaddr virt, unsigned int paddr) {
  struct pde pd_entry = pd[virt.pdi];

  if (!(pd_entry.flags & PDE_PRESENT)) {
    // TODO: allocate new pde (allocate new pte etc)
    return;
  }

  struct pte *pt = (struct pte *)(pd_entry.pte_addr << 12);
  struct pte *pt_entry = pt + virt.pti;

  if (pt_entry->flags & PTE_PRESENT) {
    // TODO: handle already mapped
    return;
  }

  pt_entry->paddr = paddr >> 12;
  pt_entry->flags = PTE_PRESENT | PTE_USER | PTE_WRITABLE;
}
