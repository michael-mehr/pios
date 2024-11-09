
// kernel_main.c

char glbl[1024]; // global char array, used for clearing bss

// returns pointer to the timer count register
// timer count register stores total microseconds since boot
unsigned long get_timer_count() {
  unsigned long *timer_count_register = 0x3f003004;
  return *timer_count_register;
}

// delays os/kernel_main by time = microseconds
void os_delay(unsigned long time) {
  unsigned long tmp = get_timer_count();
  unsigned long end = tmp + time;
  while (tmp < end) {
    tmp = get_timer_count();
  }
}

// returns the execution level the kernel is currently running at
unsigned int getEL(){
  unsigned int el;

  asm("mrs %0,CurrentEL"
      : "=r"(el)
      :
      :);

  return el;
}

// main function
void kernel_main() {

  extern int __bss_start, __bss_end;
  char *bss_start, *bss_end;

  bss_start = &__bss_start; // pointer to beginning of bss segment
  bss_end = &__bss_end; // pointer to end of bss segment

  // iterate through bss segment and write `0` to each address
  for(int *i = bss_start; i <= bss_end; i++){
    *i = 0;
  }

  // serial driver
  putc(' ');
  esp_printf(putc, "Current Execution Level is %d\r\n", getEL()); // Uses putc to print a string

  // page frame allocator
  // init_pfa_list();
  // struct ppage *allocd_list = allocate_physical_pages(10);
  // free_physical_pages(allocd_list);

  // MMU Setup
  extern struct table_descriptor_stage1 L1table; // from mmu.c
  extern struct page_descriptor_stage1 L2table; // from mmu.c
  struct table_descriptor_stage1 *L1table_ptr = &L1table; // pointer to L1 table
  // loadPageTable(L1table_ptr);
  // mapPages(0x100000, 0x200000); // map virtual address 0x100000 to physical address 0x200000


  while(1){
    esp_printf(putc, "running...\n");
    os_delay(10000000);
  }
}
