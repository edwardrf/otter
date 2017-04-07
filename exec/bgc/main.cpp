#include <Arduino.h>
#include "../../lib/PWM.h"
#include "../../lib/BGC.h"

#define BGC_OUTPUT_PIN 2
#define VERTICAL_PWM_PIN A0
#define HORIZONTAL_PWM_PIN A1
#define MODE_PWM_PIN A2

#define MAX_PWM 2000
#define MIN_PWM 1100
#define ANOMALY_MOVE_AMOUNT 200

void handle_vertical_change(volatile int last_pwm, volatile int current_pwm) {
  if (current_pwm > MAX_PWM || current_pwm < MIN_PWM)
    return;

  if (current_pwm - last_pwm > ANOMALY_MOVE_AMOUNT ||
      current_pwm - last_pwm < -ANOMALY_MOVE_AMOUNT)
    return;

  if (current_pwm > 1800) {
    bgc_up();
    return;
  }

  if (current_pwm < 1200) {
    bgc_down();
    return;
  }

  bgc_vertical_freeze();
}

void handle_horizontal_change(volatile int last_pwm, volatile int current_pwm) {
  if (current_pwm > MAX_PWM || current_pwm < MIN_PWM)
    return;

  if (current_pwm - last_pwm > ANOMALY_MOVE_AMOUNT ||
      current_pwm - last_pwm < -ANOMALY_MOVE_AMOUNT)
    return;

  if (current_pwm > 1800) {
    bgc_left();
    return;
  }

  if (current_pwm < 1200) {
    bgc_right();
    return;
  }

  bgc_horizontal_freeze();
}

void handle_mode_change(volatile int last_pwm, volatile int current_pwm) {
  if (current_pwm > MAX_PWM || current_pwm < MIN_PWM)
    return;

  if (current_pwm - last_pwm > ANOMALY_MOVE_AMOUNT ||
      current_pwm - last_pwm < -ANOMALY_MOVE_AMOUNT)
    return;

  if (current_pwm < 1200) {
    bgc_mode_no_follow();
  } else if (current_pwm > 1700) {
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
