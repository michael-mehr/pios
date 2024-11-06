// serial.c

#include "serial.h"
#include "rprintf.h"

// writes character to serial port
void putc(int data) {
  int *mu_io = (int *)MU_IO_REG;
  *mu_io = data;
}

// writes string to serial port
void uart_puts(char *str) {
  esp_printf(putc, str);
}