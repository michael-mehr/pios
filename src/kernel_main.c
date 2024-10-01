
// kernel_main.c

char glbl[1024];

unsigned long get_timer_count() {
  unsigned long *timer_count_register = 0x3f003004;
  return *timer_count_register;
}

void os_delay(unsigned long time) {
  unsigned long tmp = get_timer_count();
  unsigned long end = tmp + time;
  while (tmp < end) {
    tmp = get_timer_count();
  }
}

void kernel_main() {

  extern int __bss_start, __bss_end;
  char *bss_start, *bss_end;

  bss_start = &__bss_start;
  bss_end = &__bss_end;

  for(int *i = bss_start; i <= bss_end; i++){
    *i = 0;
  }
  
  os_delay(1000);

  putc(' ');
  esp_printf(putc, "hello world");

  while(1){
    os_delay(500000);
    esp_printf(putc, "delay");
  }
}
