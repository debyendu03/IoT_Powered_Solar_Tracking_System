#include "INA226Sensor.h"
#include "servoControl.h"
#include "wifiConnection.h"

const char* ssid="realme 6i";
const char* pass="password";

void setup() {
  Serial.begin(115200);
  setupServos();
  initINA226();
  wifiConnection(ssid,pass);
}

void loop() {
INA226Data SensorData = getINA226Value();
trackLight();
}
