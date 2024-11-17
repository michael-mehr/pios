// serial.c

#include "serial.h"
#include "delay.h"

// writes character to serial port
void putc(int data) {
    int *mu_io = (int *)MU_IO; // MU_IO register
    *mu_io = data;
}

// reads character from serial port
char getc() {
    int *mu_io = (int *)MU_IO; // MU_IO register
    while ((*mu_io & 0x01) == 0) {
        // wait for serial data to arrive
        delay_milliseconds(500);
        esp_printf(putc, "Waiting for serial data...\n");
    }
    esp_printf(putc, "getc: %c\n", (char)(*mu_io & 0xFF));
    return (char)(*mu_io & 0xFF);
}

