// shell.c

#include "shell.h"
#include "rprintf.h"
#include "serial.h"

#define MAX_COMMAND_LENGTH 128

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void shell() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        esp_printf(putc, "shell> "); // Print shell prompt

        // Read command from user
        int i = 0;
        char c;
        while (1) {
            c = getc();
            if (c == '\r' || c == '\n') { // Enter key
                break;
            }
            if (i < MAX_COMMAND_LENGTH - 1) {
                command[i++] = c;
                putc(c); // Echo character
            }
        }
        command[i] = '\0'; // Null-terminate the command

        // Process command
        if (strcmp(command, "hello") == 0) {
            esp_printf(putc, "\nHello, world!\n");
        } else if (strcmp(command, "help") == 0) {
            esp_printf(putc, "\nAvailable commands:\n");
            esp_printf(putc, "  hello - prints 'Hello, world!'\n");
            esp_printf(putc, "  help  - prints this help message\n");
        } else {
            esp_printf(putc, "\nUnrecognized command: %s\n", command);
        }
    }
}