
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

  putc(' ');
  esp_printf(putc, "Current Execution Level is %d\r\n", getEL()); // Uses putc to print a string

  while(1){
    esp_printf(putc, "running...\n");
    os_delay(10000000);
  }
}
