#include "servoControl.h"
#include "sendToBlynk.h"

const char* ssid="realme 6i";
const char* pass="password";
const char* blynkAuth="_gDiltngBrVsI1t4cG8cduavXtdPwkWu";

void setup() {
  setupServos();
  initINA226();
  initWiFiAndBlynk(blynkAuth,ssid,pass);
}

void loop() {
LightTrackingAndServoControl();
sendToBlynk();
}
