#include <Arduino.h>
#include "../lib/PWM.h"
#include "../lib/LANC.h"

#define LANC_OUTPUT_PIN 7
#define LANC_INPUT_PIN 11

#define REC_PWM_PIN A4
#define FOCUS_PWM_PIN A1
#define IRIS_PWM_PIN A2

void handle_rec_change(volatile int last_pwm, volatile int current_pwm) {
  if (last_pwm > 2000 || last_pwm < 1000 ||
      current_pwm > 2000 || current_pwm < 1000) return;

  if (0 == ((last_pwm - current_pwm) / 333)) return;

  lanc_rec();
}

void handle_focus_change(volatile int last_pwm, volatile int current_pwm) {
  if (last_pwm > 2000 || last_pwm < 1000 ||
      current_pwm > 2000 || current_pwm < 1000) return;

  if (current_pwm < 1200) {
    lanc_focus_near();
  } else if (current_pwm > 1700) {
    lanc_focus_far();
  }
}

void handle_iris_change(volatile int last_pwm, volatile int current_pwm) {
  if (last_pwm > 2000 || last_pwm < 1000 ||
      current_pwm > 2000 || current_pwm < 1000) return;

  if (current_pwm < 1200) {
    lanc_iris_dec();
  } else if (current_pwm > 1700) {
    lanc_iris_inc();
  }
}

void setup() {
  setupLANC(LANC_OUTPUT_PIN, LANC_INPUT_PIN);
  // Serial.begin(115200);

  pwm_attach1(REC_PWM_PIN, handle_rec_change);
  pwm_attach2(FOCUS_PWM_PIN, handle_focus_change);
  pwm_attach3(IRIS_PWM_PIN, handle_iris_change);
}

void loop() {
}
