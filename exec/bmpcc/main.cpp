#include <Arduino.h>
#include "../../lib/PWM.h"
#include "../../lib/LANC.h"

#define LANC_OUTPUT_PIN 7
#define LANC_INPUT_PIN 11

#define REC_PWM_PIN A0
#define FOCUS_PWM_PIN A1
#define IRIS_PWM_PIN A5

#define MAX_PWM 2000
#define MIN_PWM 1000
#define ANOMALY_MOVE_AMOUNT 200

#define DEBOUNCE 1000

volatile unsigned long last_iris_change;
volatile unsigned long last_focus_change;

volatile int rec_pwm = 1500;
volatile bool is_recording = false;

volatile int focus_pwm = 1500;
volatile int iris_pwm = 1500;

volatile int rec_action = 0;
volatile int iris_action = 0;
volatile int focus_action = 0;


void handle_rec_change(volatile int last_pwm, volatile int current_pwm) {

  rec_pwm = (9*rec_pwm + 1*current_pwm) / 10;

  if (rec_pwm > 1700 && !is_recording) {
    //lanc_rec();
    is_recording = true;
    rec_action = 1;
  } else if (rec_pwm < 1200 && is_recording) {
    //lanc_rec();
    is_recording = false;
    rec_action = 1;
  }
}

void handle_focus_change(volatile int last_pwm, volatile int current_pwm) {

  if ((millis() - last_focus_change) < DEBOUNCE)
    return;

  focus_pwm = (9*focus_pwm + 1*current_pwm) / 10;

  if (focus_pwm < 1200) {
    //lanc_focus_near();

    if (last_focus_change == 0) {
      last_focus_change = millis();
    }
    focus_action = 1;
  } else if (focus_pwm > 1700) {
    //lanc_focus_far();

    if (last_focus_change == 0) {
      last_focus_change = millis();
    }
    focus_action = -1;
  } else {
    last_focus_change = 0;
  }
}

void handle_iris_change(volatile int last_pwm, volatile int current_pwm) {

  if ((millis() - last_iris_change) < DEBOUNCE)
    return;

  iris_pwm = (9*iris_pwm + 1*current_pwm) / 10;

  if (iris_pwm < 1200) {
    //lanc_iris_dec();

    if (last_iris_change == 0) {
      // Serial.println(millis());
      last_iris_change = millis();
    }
    iris_action = 1;
  } else if (iris_pwm > 1700) {
    //lanc_iris_inc();

    if (last_iris_change == 0) {
      // Serial.println(millis());
      last_iris_change = millis();
    }
    iris_action = -1;
  } else {
    last_iris_change = 0;
  }
}

void setup() {
  lanc_setup(LANC_OUTPUT_PIN, LANC_INPUT_PIN);
  Serial.begin(115200);

  pwm_attach1(REC_PWM_PIN, handle_rec_change);
  pwm_attach2(FOCUS_PWM_PIN, handle_focus_change);
  pwm_attach3(IRIS_PWM_PIN, handle_iris_change);
}

void loop() {
  if(rec_action == 1) {
    rec_action = 0;
    lanc_rec();
  }
  delay(10);

  if(iris_action == 1) {
    iris_action = 0;
    lanc_iris_dec();
  }else if (iris_action == -1) {
    iris_action = 0;
    lanc_iris_inc();
  }
  delay(20);

  if(focus_action == 1) {
    focus_action = 0;
    lanc_focus_near();
  }else if (focus_action == -1) {
    focus_action = 0;
    lanc_focus_far();
  }
  delay(20);
}
