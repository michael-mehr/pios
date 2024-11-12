
// page.c

#include "page.h"
#include <stddef.h>

struct ppage physical_page_array[128]; // 128 pages, each 2mb in length covers 256 megs of memory

struct ppage *free_ppage_list;

void add_page_to_list(struct ppage **list_head, struct ppage *new_page) {
  new_page->next = *list_head;
  *list_head = new_page;
}

struct ppage *remove_page_from_list(struct ppage **list) {
  struct ppage *removed_page = *list;
  *list = removed_page->next;
  removed_page->next = NULL;
  return removed_page;
}

void init_pfa_list(void) {
  unsigned int num_pages = sizeof(physical_page_array) / sizeof(physical_page_array[0]);
  free_ppage_list = physical_page_array; // points to first page in array
  for (int page_num = 0; page_num < num_pages; page_num++) {
    struct ppage *current_page = &physical_page_array[page_num];
    current_page->physical_addr = &physical_page_array[page_num];
    add_page_to_list(&free_ppage_list, current_page);
  }
}

struct ppage *allocate_physical_pages(unsigned int npages) {
  struct ppage *alloc_ppages;
  if (npages) {
    for (unsigned int i = 0; i < npages; i++) {
      add_page_to_list(&alloc_ppages, remove_page_from_list(&free_ppage_list));
    }
  }
  return alloc_ppages;
}

void free_physical_pages(struct ppage *ppage_list) {
  if (ppage_list) {
    while (ppage_list->next) {
      add_page_to_list(&free_ppage_list, remove_page_from_list(&ppage_list));
    }
    add_page_to_list(&free_ppage_list, remove_page_from_list(&ppage_list));
  }
}

