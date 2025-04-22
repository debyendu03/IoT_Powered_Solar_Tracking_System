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
int servohori = 180;  // initial servo horizontal position 180
int servovert = 45;  // initial servo vertical position 45

// Timing control
unsigned long lastMoveTime = 0;
const unsigned long moveInterval = 50; // Move every 50ms for smoothness

// Define the light threshold to decide if it's outdoor or indoor
const int lightThreshold = 1000; // Adjust based on environment

// Setup servos
void setupServos() {
  horizontal.attach(26);
  vertical.attach(25);
  horizontal.write(servohori);
  vertical.write(servovert);
}

// Function to read LDR and calculate average
int readLDR(int pin) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(pin);
    delayMicroseconds(500); // Very tiny delay between reads (~0.5ms)
  }
  return sum / 5;
}

// Light Tracking and Servo Control
void LightTrackingAndServoControl() {
  unsigned long currentMillis = millis();
  
  // Only update at defined interval
  if (currentMillis - lastMoveTime >= moveInterval) {
    lastMoveTime = currentMillis;
    
    // Read the LDR values
    int lt = readLDR(ldrlt);
    int rt = readLDR(ldrrt);
    int ld = readLDR(ldrld);
    int rd = readLDR(ldrrd);

    // Calculate averages
    int avt = (lt + rt) >> 1;
    int avd = (ld + rd) >> 1;

    // Calculate differences
    int dvert = avt - avd;
    int dhoriz = lt - rt + ld - rd;

    // Determine outdoor/indoor
    int avgLight = (lt + rt + ld + rd) / 4;
    int tol = (avgLight > lightThreshold) ? 50 : 200;

    // Adjust vertical servo
    if (abs(dvert) > tol) {
      if (dvert > 0 && servovert < servovertLimitHigh) servovert++;
      else if (dvert < 0 && servovert > servovertLimitLow) servovert--;
      vertical.write(servovert);
    }

    // Adjust horizontal servo
    if (abs(dhoriz) > tol) {
      if (dhoriz < 0 && servohori < servohoriLimitHigh) servohori++;
      else if (dhoriz > 0 && servohori > servohoriLimitLow) servohori--;
      horizontal.write(servohori);
    }
  }
}
