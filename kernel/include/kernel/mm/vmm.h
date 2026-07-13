#include <stdint.h>

#define PDE_PRESENT 1 << 0
#define PDE_WRITABLE 1 << 1
#define PDE_USER 1 << 2
#define PDE_WRITE_THROUGH 1 << 3
#define PDE_DISABLE_CACHE 1 << 4
#define PDE_ACCESSED 1 << 5
// TODO: available missing
#define PDE_PAGE_SIZE 1 << 7

#define PTE_PRESENT 1 << 0
#define PTE_WRITABLE 1 << 1
#define PTE_USER 1 << 2
#define PTE_WRITE_THROUGH 1 << 3
#define PTE_DISABLE_CACHE 1 << 4
#define PTE_ACCESSED 1 << 5
#define PTE_DIRTY 1 << 6
#define PTE_PAT 1 << 7
#define PTE_GLOBAL 1 << 8
// TODO: available

#define PD_ENTRIES 1024
#define PT_ENTRIES 1024

struct vaddr {
  unsigned int offset : 12;
  unsigned int pti : 10;
  unsigned int pdi : 10;
};

struct pde {
  unsigned int flags : 12;
  unsigned int pte_addr : 20;
};

struct pte {
  unsigned int flags : 12;
  unsigned int paddr : 20;
};

extern void load_page_directory(struct pde *);
extern void enable_paging();

void init_page_directory(struct pde *pd);
void init_identity_page_table(struct pte *pt);

void map_page(struct pde *pd, struct vaddr virt, unsigned int paddr);
