// serial.c

void putc(int data) {
  int *mu_io = 0x3F215040;
  *mu_io = data;
}
