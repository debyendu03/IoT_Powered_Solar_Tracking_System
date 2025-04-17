#include "servoControl.h"

#include <ESP32Servo.h>

// Servo objects and variables
Servo horizontal; 
Servo vertical;

// Servo limits
const int servohoriLimitHigh = 175;
const int servohoriLimitLow = 5;
const int servovertLimitHigh = 140;
const int servovertLimitLow = 1;

// LDR pins
const int ldrlt = 35; // Top Left
const int ldrrt = 32; // Top Right
const int ldrld = 34; // Bottom Left
const int ldrrd = 33; // Bottom Right

// Global tracking variables
int servohori = 180; // Current horizontal position
int servovert = 45;  // Current vertical position

void setupServos() {
  horizontal.attach(26);
  vertical.attach(25);
  horizontal.write(0);
  vertical.write(0);
  //delay(2500); // Initialization delay
}

void trackLight() {
  // Read all LDR sensors
  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);

  const int tol = 200; // Light difference threshold
  const int dtime = 10; // Loop delay

  // Calculate averages
  int avt = (lt + rt) / 2; // Top average
  int avd = (ld + rd) / 2; // Bottom average
  int avl = (lt + ld) / 2; // Left average
  int avr = (rt + rd) / 2; // Right average

  // Calculate differences
  int dvert = avt - avd;
  int dhoriz = avl - avr;

  // Vertical tracking
  if (abs(dvert) > tol) {
    if (avt > avd) {
      servovert = min(servovert + 1, servovertLimitHigh);
    } else {
      servovert = max(servovert - 1, servovertLimitLow);
    }
    vertical.write(servovert);
  }

  // Horizontal tracking
  if (abs(dhoriz) > tol) {
    if (avl > avr) {
      servohori = max(servohori - 1, servohoriLimitLow);
    } else {
      servohori = min(servohori + 1, servohoriLimitHigh);
    }
    horizontal.write(servohori);
  }

  delay(dtime);
}
