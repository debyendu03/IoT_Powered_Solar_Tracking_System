#include "servoControl.h"
#include <ESP32Servo.h>

// Servo objects
Servo horizontal, vertical;

// Servo limits
const int servohoriLimitHigh = 175, servohoriLimitLow = 5;
const int servovertLimitHigh = 140, servovertLimitLow = 1;

// LDR pins
const int ldrlt = 35, ldrrt = 32, ldrld = 34, ldrrd = 33;

// Current servo positions
int servohori = 180, servovert = 45;

void setupServos() {
  horizontal.attach(26);
  vertical.attach(25);
  horizontal.write(0);
  vertical.write(0);
}

void LightTrackingAndServoControl() {
  int lt = analogRead(ldrlt), rt = analogRead(ldrrt);
  int ld = analogRead(ldrld), rd = analogRead(ldrrd);

  int avt = (lt + rt) >> 1, avd = (ld + rd) >> 1; // average top/bottom
  int avl = (lt + ld) >> 1, avr = (rt + rd) >> 1; // average left/right

  int dvert = avt - avd, dhoriz = avl - avr;

  const int tol = 200;

  if (abs(dvert) > tol) {
    servovert = constrain(servovert + (dvert > 0 ? 1 : -1), servovertLimitLow, servovertLimitHigh);
    vertical.write(servovert);
  }

  if (abs(dhoriz) > tol) {
    servohori = constrain(servohori + (dhoriz < 0 ? 1 : -1), servohoriLimitLow, servohoriLimitHigh);
    horizontal.write(servohori);
  }

  delay(10);
}