// page.c

#include "page.h"
#include <stddef.h>
#include <stdio.h>

#define PAGE_SIZE 4096 // 4kb
#define NUM_PAGES 128

struct ppage physical_page_array[NUM_PAGES]; // 128 pages, each 2mb in length covers 256 megs of memory

struct ppage *free_ppage_list;

void add_page_to_list(struct ppage **list_head, struct ppage *new_page) {
  if (list_head == NULL || new_page == NULL) return;
  new_page->next = *list_head;
  new_page->prev = NULL;

  if (*list_head != NULL) {
    (*list_head)->prev = new_page;
  }
  *list_head = new_page;
}

struct ppage *remove_page_from_list(struct ppage **list_head) {
  if (list_head == NULL || *list_head == NULL) return NULL; // no page to remove
  struct ppage *removed_page = *list_head;
  *list_head = removed_page->next;
  if (*list_head != NULL) {
    (*list_head)->prev = NULL;
  }
  // remove pointers from removed page
  removed_page->next = NULL;
  removed_page->prev = NULL;
  return removed_page;
}

void init_pfa_list(void) {
  free_ppage_list = &physical_page_array[0]; // points to first page in array
  for (int i = 0; i < NUM_PAGES; i++) {
    physical_page_array[i].physical_addr = (void *)(unsigned int)(i * PAGE_SIZE);
    if (i == 0) {
      physical_page_array[i].prev = NULL; // first page in array
    } else {
      physical_page_array[i].prev = &physical_page_array[i - 1]; // points to previous page
    }
    if (i == NUM_PAGES - 1) {
      physical_page_array[i].next = NULL; // last page in array
    } else {
      physical_page_array[i].next = &physical_page_array[i + 1]; // points to next page
    }
  }
}

struct ppage *allocate_page(struct ppage **list_head) {
  return remove_page_from_list(list_head);
}

struct ppage *allocate_physical_pages(unsigned int npages) {
  struct ppage *alloc_ppages = NULL;
  if (npages) {
    for (unsigned int i = 0; i < npages; i++) {
      struct ppage *page = allocate_page(&free_ppage_list);
      if (page == NULL) {
        break; // stops if no more pages are available
      }
      add_page_to_list(&alloc_ppages, page);
    }
  }
  return alloc_ppages;
}

void free_physical_pages(struct ppage *ppage_list) {
  while (ppage_list != NULL) {
    struct ppage *next_page = ppage_list->next; // store next pointer
    add_page_to_list(&free_ppage_list, ppage_list);
    ppage_list = next_page; // move to the next page
  }
}

// void print_ppage_list(struct ppage *list_head) {
//   struct ppage *tmp = list_head;
//   while (tmp != NULL) {
//     printf("Physical Address: %p\n", tmp->physical_addr);
//     tmp = tmp->next;
//   }
// }

// int main() {
//   init_pfa_list();
//   // print_ppage_list(free_ppage_list);
//   struct ppage *allocd_list = allocate_physical_pages(8);
//   // print_ppage_list(allocd_list);
//   // print_ppage_list(free_ppage_list);
//   free_physical_pages(allocd_list);
//   return 0; 
// }
