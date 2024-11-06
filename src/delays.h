// delays.h

#define TIMER_REGISTER 0x3f003004

unsigned long get_timer_count();
void delay_cycles(unsigned int cycles);
void delay_ms(unsigned int ms); 