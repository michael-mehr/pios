// serial.c

// writes character to serial port
void putc(int data) {
  int *mu_io = 0x3F215040; // MU_IO register
  *mu_io = data;
}

// reads character from serial port
char getc() {
  int *mu_io = 0x3F215040; // MU_IO register
  return *mu_io;
}

