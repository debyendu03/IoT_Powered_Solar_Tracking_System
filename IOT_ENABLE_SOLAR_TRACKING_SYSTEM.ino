#include "INA226Sensor.h"

void setup() {
  Serial.begin(115200);
   
  initINA226();
}

void loop() {
INA226Data SensorData = getINA226Value();
delay(1500);

}
