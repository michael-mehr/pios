// kernel_main.c

#include "fat.h"
#include "serial.h"
#include "rprintf.h"
#include "delays.h"

char glbl[1024]; // global char array, used for clearing bss

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

  // FAT filesystem initialization
  fatInit();

  char file_name[] = "TEST";
  char *fn = &file_name;
  char file_extension[] = "TXT";
  char *fe = &file_extension;
  
  esp_printf(putc, "Opening file %s\r\n", fn);

  struct file *f;

  f = fatOpen(fn, fe);
  if (f) {
    esp_printf(putc, "File %s opened successfully\r\n", &file_name[0]);
  } else {
    esp_printf(putc, "Failed to open file %s.%s\n", fn, fe);
  }

  // main loop
  while(1){
    uart_puts("running...\n");
    wait_msec(2000);
  }
}
