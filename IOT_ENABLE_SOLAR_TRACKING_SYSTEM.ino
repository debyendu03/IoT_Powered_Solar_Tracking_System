#include "INA226Sensor.h"
#include "servoControl.h"

void setup() {
  Serial.begin(115200);
  setupServos();
  initINA226();
}

void loop() {
INA226Data SensorData = getINA226Value();
//delay(1500);
trackLight();
}
