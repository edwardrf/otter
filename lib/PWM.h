#ifndef BMPCC_RC_PWM
#define BMPCC_RC_PWM

void exec_without_pcint(void (*fn)(void));

void pwm_attach1(int pin, void (*handler)(unsigned long));

void pwm_attach2(int pin, void (*handler)(unsigned long));

void pwm_attach3(int pin, void (*handler)(unsigned long));

#endif
