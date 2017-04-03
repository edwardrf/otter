#include "TimerOne.h"
#define GOHI() \
  digitalWrite(output_pin_, HIGH); \
  delayMicroseconds(600); \
  digitalWrite(output_pin_, LOW);

// define modes
#define NORMAL 900

int output_pin_;

volatile int mode;
volatile int horizontal;
volatile int vertical;

void bgc_setup(int pin) {
  output_pin_ = pin;
  pinMode(output_pin_, OUTPUT);
  digitalWrite(output_pin_, LOW);

  mode = NORMAL;
  freeze();

  Timer1.initialize(40000);
  Timer1.attachInterrupt(send);
}

void bgc_horizontal_freeze() {
  horizontal = 900;
}

void bgc_vertical_freeze() {
  vertical = 900;
}

void bgc_right() {
  horizontal = 400;
}

void bgc_left() {
  horizontal = 1400;
}

void bgc_down() {
  vertical = 400;
}

void bgc_up() {
  vertical = 1400;
}

void send() {
  GOHI();
  delayMicroseconds(horizontal);
  GOHI();
  delayMicroseconds(vertical);
  GOHI();
  delayMicroseconds(mode);
  GOHI();
}
