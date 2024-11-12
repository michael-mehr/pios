
// shell.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

int main(int argc, char **argv) {  // clone of shittyshell
  char *line, **argz;
  __pid_t pid, wpid;
  size_t bufsize = 0;

  while(1) {
    printf("$");
    line = NULL;
    getline(&line, &bufsize, stdin);
    line[strlen(line) - 1] = '\0'; // remove newline character
    pid = fork();
    if(pid == 0) {  // child process
      char *argz[2];
      argz[0] = line;
      argz[1] = NULL;
      if(execv(line, argz) == -1) {
        perror("nsh");
      }
    } else {  // parent process
      line = NULL;
      argz = NULL;
    }
  }
}