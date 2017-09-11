#include <Arduino.h>
#include "../../lib/PWM.h"
#include "../../lib/LANC.h"

#define LANC_OUTPUT_PIN 7
#define LANC_INPUT_PIN 11

#define REC_PWM_PIN A0
#define FOCUS_PWM_PIN A1
#define IRIS_PWM_PIN A5

#define DELAY 1000

#define S_FOCUS_NONE 0
#define S_FOCUS_FAR 1
#define S_FOCUS_NEAR 2

#define S_IRIS_NONE 0
#define S_IRIS_INC 1
#define S_IRIS_DEC 2
 
#define S_RECORDING_NONE 0
#define S_RECORDING_TOGGLE 1

volatile unsigned long last_focus_near;
volatile unsigned long last_focus_far;
volatile unsigned long last_iris_dec;
volatile unsigned long last_iris_inc;

volatile int rec_pwm = 1500;
volatile int focus_pwm = 1500;
volatile int iris_pwm = 1500;

volatile bool is_recording = false;

volatile int signal_recording = S_RECORDING_NONE;
volatile int signal_focus = S_FOCUS_NONE;
volatile int signal_iris = S_IRIS_NONE;


void handle_rec_change(unsigned long pwm) {

  rec_pwm = (9*rec_pwm + 1*pwm) / 10;

  if (rec_pwm > 1700 && !is_recording) {
    is_recording = true;

    signal_recording = S_RECORDING_TOGGLE;
  } else if (rec_pwm < 1200 && is_recording) {
    is_recording = false;

    signal_recording = S_RECORDING_TOGGLE;
  } else {
    signal_recording = S_RECORDING_NONE;
  }
}

void handle_focus_change(unsigned long pwm) {

  focus_pwm = (9*focus_pwm + 1*pwm) / 10;

  if (focus_pwm < 1200) {
    signal_focus = S_FOCUS_NEAR;
  } else if (focus_pwm > 1700) {
    signal_focus = S_FOCUS_FAR;
  } else {
    signal_focus = S_FOCUS_NONE;
  }
}

void handle_iris_change(unsigned long pwm) {

  iris_pwm = (9*iris_pwm + 1*pwm) / 10;

  if (iris_pwm < 1200) {
    signal_iris = S_IRIS_DEC;
  } else if (iris_pwm > 1700) {
    signal_iris = S_IRIS_INC;
  } else {
    signal_iris = S_IRIS_NONE;
  }
}

void setup() {
  lanc_setup(LANC_OUTPUT_PIN, LANC_INPUT_PIN);
  Serial.begin(115200);

  pwm_attach1(REC_PWM_PIN, handle_rec_change);
  pwm_attach2(FOCUS_PWM_PIN, handle_focus_change);
  pwm_attach3(IRIS_PWM_PIN, handle_iris_change);
}

// each lanc command takes at least 8.69ms
// pwm duration is 2ms
void loop() {
  if (signal_recording == S_RECORDING_TOGGLE) {
    exec_without_pcint(lanc_rec);
  }

  // millis() takes 50 days to overflow, safe to ignore
  // https://www.arduino.cc/en/Reference/Millis
  if (signal_focus == S_FOCUS_NEAR
      && (millis() - last_focus_near) > DELAY) {

    exec_without_pcint(lanc_focus_near);

    last_focus_near = millis();
  } else if (signal_focus == S_FOCUS_FAR
      && (millis() - last_focus_far) > DELAY) {

    exec_without_pcint(lanc_focus_far);

    last_focus_far = millis();
  }

  if (signal_iris == S_IRIS_DEC
      && (millis() - last_iris_dec) > DELAY) {

    exec_without_pcint(lanc_iris_dec);

    last_iris_dec = millis();
  } else if (signal_iris == S_IRIS_INC
      && (millis() - last_iris_inc) > DELAY) {

    exec_without_pcint(lanc_iris_inc);

    last_iris_inc = millis();
  }
}
