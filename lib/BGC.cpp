#include "TimerOne.h"
#define GOHI() \
  digitalWrite(output_pin_, HIGH); \
  delayMicroseconds(600); \
  digitalWrite(output_pin_, LOW);

// define modes
#define VALUE_MIDDLE 900
#define VALUE_LOW 400
#define VALUE_HIGH 1400

int output_pin_;

volatile int mode;
volatile int horizontal;
volatile int vertical;

void send() {
  GOHI();
  delayMicroseconds(horizontal);
  GOHI();
  delayMicroseconds(vertical);
  GOHI();
  delayMicroseconds(mode);
  GOHI();
}

void bgc_horizontal_freeze() {
  horizontal = VALUE_MIDDLE;
}

void bgc_vertical_freeze() {
  vertical = VALUE_MIDDLE;
}

void bgc_right() {
  horizontal = VALUE_LOW;
}

void bgc_left() {
  horizontal = VALUE_HIGH;
}

void bgc_down() {
  vertical = VALUE_LOW;
}

void bgc_up() {
  vertical = VALUE_HIGH;
}

void bgc_mode_follow() {
  mode = VALUE_MIDDLE;
}

void bgc_mode_no_follow() {
  mode = VALUE_LOW;
}

void bgc_setup(int pin) {
  output_pin_ = pin;
  pinMode(output_pin_, OUTPUT);
  digitalWrite(output_pin_, LOW);

  bgc_horizontal_freeze();
  bgc_vertical_freeze();
  bgc_mode_no_follow();

  Timer1.initialize(40000);
  Timer1.attachInterrupt(send);
}
