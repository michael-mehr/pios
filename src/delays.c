// delays.c

#include "delays.h"

unsigned long get_timer_count() {
  unsigned long *timer_count_register = TIMER_REGISTER;
  return *timer_count_register;
}

// delays OS by num cycles, where each cycle is 1 microsecond
void wait_cycles(unsigned int cycles) {
  unsigned long start = get_timer_count();
  unsigned long end = start + cycles;
  while (get_timer_count() < end) {
    // do nothing
  }
}

// delays OS by num milliseconds
void wait_msec(unsigned int ms) {
  wait_cycles(ms * 1000);
}