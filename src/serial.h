// serial.h

#define MU_IO_REG 0x3F215040

void putc(int data);
void uart_puts(char *str);