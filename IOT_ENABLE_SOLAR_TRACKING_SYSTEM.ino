#include <WiFi.h>
#include "servoControl.h"
#include "sendToBlynk.h"

const char* ssid="realme 6i";
const char* pass="password";
const char* blynkAuth="_gDiltngBrVsI1t4cG8cduavXtdPwkWu";

void setup() {
  Serial.begin(115200);
  setupServos();
  initINA226();
  WiFi.begin(ssid,pass);
  initBlynk(blynkAuth,ssid,pass);
}

void loop() {
LightTrackingAndServoControl();
sendToBlynk();
}
