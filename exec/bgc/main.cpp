#include <Arduino.h>
#include "../lib/PWM.h"
#include "../lib/BGC.h"

// TODO
#define BGC_OUTPUT_PIN 1
#define HORIZONTAL_PWM_PIN 2
#define VERTICAL_PWM_PIN 3

void handle_horizontal_change(volatile int last_pwm, volatile int current_pwm) {
  if (last_pwm > 2000 || last_pwm < 1000 ||
      current_pwm > 2000 || current_pwm < 1000) return;

  if (current_pwm > 1700) {
    bgc_right();
    return;
  }

  if (current_pwm < 1100) {
    bgc_left();
    return;
  }

  bgc_horizontal_freeze();
}

void handle_vertical_change(volatile int last_pwm, volatile int current_pwm) {
  if (last_pwm > 2000 || last_pwm < 1000 ||
      current_pwm > 2000 || current_pwm < 1000) return;

  if (current_pwm > 1700) {
    bgc_down();
    return;
  }

  if (current_pwm < 1100) {
    bgc_top();
    return;
  }

  bgc_vertical_freeze();
}

void setup() {
  bgc_setup(BGC_OUTPUT_PIN);
  /* Serial.begin(115200); */

  pwm_attach1(HORIZONTAL_PWM_PIN, handle_horizontal_change);
  pwm_attach2(VERTICAL_PWM_PIN, handle_vertical_change);
}

void loop() {
}
