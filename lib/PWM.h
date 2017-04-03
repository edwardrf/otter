#ifndef BMPCC_RC_PWM
#define BMPCC_RC_PWM

void pwm_attach1(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach2(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach3(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach4(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach5(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach6(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach7(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

void pwm_attach8(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

#endif
