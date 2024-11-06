// delays.h

#define TIMER_REGISTER 0x3f003004

unsigned long get_timer_count();
void wait_cycles(unsigned int cycles);
void wait_ms(unsigned int ms); 