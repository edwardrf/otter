#include <Arduino.h>
#include "PinChangeInterrupt.h"

// https://github.com/NicoHood/PinChangeInterrupt#pinchangeinterrupt-table

volatile unsigned long start_time1_ = 0;
volatile unsigned long start_time2_ = 0;
volatile unsigned long start_time3_ = 0;

int pcint1_;
int pcint2_;
int pcint3_;

void (*handler1_)(unsigned long);
void (*handler2_)(unsigned long);
void (*handler3_)(unsigned long);

void disable_pcint_all() {
  disablePCINT(pcint1_);
  disablePCINT(pcint2_);
  disablePCINT(pcint3_);

  start_time1_ = 0;
  start_time2_ = 0;
  start_time3_ = 0;
}

void enable_pcint_all() {
  enablePCINT(pcint1_);
  enablePCINT(pcint2_);
  enablePCINT(pcint3_);
}

void exec_without_pcint(void (*fn)(void)) {
  disable_pcint_all();
  fn();
  enable_pcint_all();
}

void on_pwm_change1() {
  unsigned long pwm = 0;

  uint8_t trigger = getPinChangeInterruptTrigger(pcint1_);
  if (trigger == RISING) {
    start_time1_ = micros();
  } else if (trigger == FALLING && start_time1_ != 0) {
    pwm = micros() - start_time1_;
  }

  handler1_(pwm);
}

void on_pwm_change2() {
  unsigned long pwm = 0;

  uint8_t trigger = getPinChangeInterruptTrigger(pcint2_);
  if (trigger == RISING) {
    start_time2_ = micros();
  } else if (trigger == FALLING && start_time2_ != 0) {
    pwm = micros() - start_time2_;
  }

  handler2_(pwm);
}

void on_pwm_change3() {
  unsigned long pwm = 0;

  uint8_t trigger = getPinChangeInterruptTrigger(pcint3_);
  if (trigger == RISING) {
    start_time3_ = micros();
  } else if (trigger == FALLING && start_time3_ != 0) {
    pwm = micros() - start_time3_;
  }

  handler3_(pwm);
}


void pwm_attach1(int pin, void (*handler)(unsigned long)) {
  pcint1_ = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint1_, INPUT_PULLUP);

  handler1_ = handler;

  attachPCINT(pcint1_, on_pwm_change1, CHANGE);
}

void pwm_attach2(int pin, void (*handler)(unsigned long)) {
  pcint2_ = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint2_, INPUT_PULLUP);

  handler2_ = handler;

  attachPCINT(pcint2_, on_pwm_change2, CHANGE);
}

void pwm_attach3(int pin, void (*handler)(unsigned long)) {
  pcint3_ = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint3_, INPUT_PULLUP);

  handler3_ = handler;

  attachPCINT(pcint3_, on_pwm_change3, CHANGE);
}
