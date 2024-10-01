// page.h

struct ppage {
  struct ppage *next;
  struct ppage *prev;
  void *physical_addr;
};