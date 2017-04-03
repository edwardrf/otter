#include <Arduino.h>
#include "PinChangeInterrupt.h"

// https://github.com/NicoHood/PinChangeInterrupt#pinchangeinterrupt-table

// register 1
volatile int current_pwm1_ = 0;
volatile int last_pwm1_ = 0;
volatile int start_time1_ = 0;
int pin1_;

void (*handler1_)(volatile int, volatile int);

void onPWMChange1() {
  if (digitalRead(pin1_) == HIGH) {
    start_time1_ = micros();
    return;
  }

  if (start_time1_ == 0) {
    return;
  }

  last_pwm1_ = current_pwm1_;
  current_pwm1_ = micros() - start_time1_;

  handler1_(last_pwm1_, current_pwm1_);
}

void pwm_attach1(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin1_ = pin;
  handler1_ = handler;

  attachPCINT(pcint, onPWMChange1, CHANGE);
}

// register 2
volatile int current_pwm2_ = 0;
volatile int last_pwm2_ = 0;
volatile int start_time2_ = 0;
int pin2_;

void (*handler2_)(volatile int, volatile int);

void onPWMChange2() {
  if (digitalRead(pin2_) == HIGH) {
    start_time2_ = micros();
    return;
  }

  if (start_time2_ == 0) {
    return;
  }

  last_pwm2_ = current_pwm2_;
  current_pwm2_ = micros() - start_time2_;

  handler2_(last_pwm2_, current_pwm2_);
}

void pwm_attach2(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin2_ = pin;
  handler2_ = handler;

  attachPCINT(pcint, onPWMChange2, CHANGE);
}

// register 3
volatile int current_pwm3_ = 0;
volatile int last_pwm3_ = 0;
volatile int start_time3_ = 0;
int pin3_;

void (*handler3_)(volatile int, volatile int);

void onPWMChange3() {
  if (digitalRead(pin3_) == HIGH) {
    start_time3_ = micros();
    return;
  }

  if (start_time3_ == 0) {
    return;
  }

  last_pwm3_ = current_pwm3_;
  current_pwm3_ = micros() - start_time3_;

  handler3_(last_pwm3_, current_pwm3_);
}

void pwm_attach3(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin3_ = pin;
  handler3_ = handler;

  attachPCINT(pcint, onPWMChange3, CHANGE);
}

// register 4
volatile int current_pwm4_ = 0;
volatile int last_pwm4_ = 0;
volatile int start_time4_ = 0;
int pin4_;

void (*handler4_)(volatile int, volatile int);

void onPWMChange4() {
  if (digitalRead(pin4_) == HIGH) {
    start_time4_ = micros();
    return;
  }

  if (start_time4_ == 0) {
    return;
  }

  last_pwm4_ = current_pwm4_;
  current_pwm4_ = micros() - start_time4_;

  handler4_(last_pwm4_, current_pwm4_);
}

void pwm_attach4(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin4_ = pin;
  handler4_ = handler;

  attachPCINT(pcint, onPWMChange4, CHANGE);
}

// register 5
volatile int current_pwm5_ = 0;
volatile int last_pwm5_ = 0;
volatile int start_time5_ = 0;
int pin5_;

void (*handler5_)(volatile int, volatile int);

void onPWMChange5() {
  if (digitalRead(pin5_) == HIGH) {
    start_time5_ = micros();
    return;
  }

  if (start_time5_ == 0) {
    return;
  }

  last_pwm5_ = current_pwm5_;
  current_pwm5_ = micros() - start_time5_;

  handler5_(last_pwm5_, current_pwm5_);
}

void pwm_attach5(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin5_ = pin;
  handler5_ = handler;

  attachPCINT(pcint, onPWMChange5, CHANGE);
}

// register 6
volatile int current_pwm6_ = 0;
volatile int last_pwm6_ = 0;
volatile int start_time6_ = 0;
int pin6_;

void (*handler6_)(volatile int, volatile int);

void onPWMChange6() {
  if (digitalRead(pin6_) == HIGH) {
    start_time6_ = micros();
    return;
  }

  if (start_time6_ == 0) {
    return;
  }

  last_pwm6_ = current_pwm6_;
  current_pwm6_ = micros() - start_time6_;

  handler6_(last_pwm6_, current_pwm6_);
}

void pwm_attach6(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin6_ = pin;
  handler6_ = handler;

  attachPCINT(pcint, onPWMChange6, CHANGE);
}

// register 7
volatile int current_pwm7_ = 0;
volatile int last_pwm7_ = 0;
volatile int start_time7_ = 0;
int pin7_;

void (*handler7_)(volatile int, volatile int);

void onPWMChange7() {
  if (digitalRead(pin7_) == HIGH) {
    start_time7_ = micros();
    return;
  }

  if (start_time7_ == 0) {
    return;
  }

  last_pwm7_ = current_pwm7_;
  current_pwm7_ = micros() - start_time7_;

  handler7_(last_pwm7_, current_pwm7_);
}

void pwm_attach7(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin7_ = pin;
  handler7_ = handler;

  attachPCINT(pcint, onPWMChange7, CHANGE);
}

// register 8
volatile int current_pwm8_ = 0;
volatile int last_pwm8_ = 0;
volatile int start_time8_ = 0;
int pin8_;

void (*handler8_)(volatile int, volatile int);

void onPWMChange8() {
  if (digitalRead(pin8_) == HIGH) {
    start_time8_ = micros();
    return;
  }

  if (start_time8_ == 0) {
    return;
  }

  last_pwm8_ = current_pwm8_;
  current_pwm8_ = micros() - start_time8_;

  handler8_(last_pwm8_, current_pwm8_);
}

void pwm_attach8(int pin, void (*handler)(volatile int, volatile int)) {
  int pcint = digitalPinToPinChangeInterrupt(pin);
  pinMode(pcint, INPUT_PULLUP);

  pin8_ = pin;
  handler8_ = handler;

  attachPCINT(pcint, onPWMChange8, CHANGE);
}
