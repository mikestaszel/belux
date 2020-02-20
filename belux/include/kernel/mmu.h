#ifndef _KERNEL_MMU_H
#define _KERNEL_MMU_H

#define KERNEL_PAGE_OFFSET 0xC0000000

void page_table_set(uintptr_t address, uintptr_t page_addr, uint16_t flags);
void* phys_to_virt(void* ptr);
void* virt_to_phys(void* ptr);

#endif
