
// page.c

#include "page.h"
#include "list.c"

struct ppage physical_page_array[128]; // 128 pages, each 2mb in length covers 256 megs of memory



void init_pfa_list(void) {
  unsigned int arraySize = sizeof(physical_page_array) / sizeof(physical_page_array[0]);
  
}

struct ppage *allocate_physical_pages(unsigned int npages) {

}

void free_physical_pages(struct ppage *ppage_list) {

}