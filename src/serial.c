// serial.c

#define MU_IO 0x3F215040

void putc(int data) {
  char *mu_io = MU_IO;
  mu_io = data;
}
