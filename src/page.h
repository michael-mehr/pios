// page.h

struct ppage {
  struct ppage *next;
  struct ppage *prev;
  void *physical_addr;
};

void add_page_to_list(struct ppage **list_head, struct ppage *new_page);
struct ppage *remove_page_from_list(struct ppage **list);
void init_pfa_list(void);
struct ppage *allocate_physical_pages(unsigned int npages);
void free_physical_pages(struct ppage *ppage_list);