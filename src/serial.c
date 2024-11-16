// serial.c

int *mu_io = 0x3F215040; // MU_IO register

// writes character to serial port
void putc(int data) {
  *mu_io = data;
}

// reads character from serial port
char getc() {
  return *mu_io;
}

