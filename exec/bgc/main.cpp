#include <Arduino.h>
#include "../../lib/PWM.h"
#include "../../lib/BGC.h"

#define BGC_OUTPUT_PIN 10 // D10
#define VERTICAL_PWM_PIN A0
#define HORIZONTAL_PWM_PIN A1
#define MODE_PWM_PIN A2

void handle_vertical_change(unsigned long pwm) {
  if (pwm > 1800) {
    bgc_up();
    return;
  }

  if (pwm < 1200) {
    bgc_down();
    return;
  }

  bgc_vertical_freeze();
}

void handle_horizontal_change(unsigned long pwm) {
  if (pwm > 1800) {
    bgc_left();
    return;
  }

  if (pwm < 1200) {
    bgc_right();
    return;
  }

  bgc_horizontal_freeze();
}

void handle_mode_change(unsigned long pwm) {
  if (pwm < 1200) {
    bgc_mode_no_follow();
  } else if (pwm > 1700) {
    bgc_mode_follow();
  }
}

void setup() {
  bgc_setup(BGC_OUTPUT_PIN);
  // Serial.begin(115200); 

  pwm_attach1(VERTICAL_PWM_PIN, handle_vertical_change);
  pwm_attach2(HORIZONTAL_PWM_PIN, handle_horizontal_change);
  pwm_attach3(MODE_PWM_PIN, handle_mode_change);
}

void loop() {
  // bgc_left();
  // delay(2000);
  // bgc_right();
  // delay(2000);
}
