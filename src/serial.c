// serial.c

void putc(int data) {
  int *mu_io = (int *) 0x3F215040;
  *mu_io = data;
}
