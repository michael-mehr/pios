// delay.c

#include "delay.h"

// returns pointer to the timer count register
// timer count register stores total microseconds since boot
unsigned long get_timer_count() {
  unsigned long *timer_count_register = 0x3f003004;
  return *timer_count_register;
}

// delays os/kernel_main by time = microseconds
void delay_microseconds(unsigned long time) {
  unsigned long tmp = get_timer_count();
  unsigned long end = tmp + time;
  while (tmp < end) {
    tmp = get_timer_count();
  }
}

// delays os/kernel_main by time = milliseconds
void delay_milliseconds(unsigned long time) {
  delay_microseconds(time * 1000);
}

// delay os/kernel_main by time = seconds
void delay_seconds(unsigned long time) {
  delay_milliseconds(time * 1000);
}