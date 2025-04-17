#include "INA226Sensor.h"
#include <Wire.h>
#include <INA226_WE.h>

#define I2C_ADDRESS 0x40
INA226_WE ina226(I2C_ADDRESS); 

void initINA226() {
  Wire.begin(21, 22);
  ina226.init();
  ina226.setResistorRange(0.1, 1.3); // 0.1 Ohm shunt, up to 1.3A
  ina226.setCorrectionFactor(0.93);
  ina226.waitUntilConversionCompleted();
}

INA226Data getINA226Value() {
  INA226Data data;
  data.shuntVoltage_mV = ina226.getShuntVoltage_mV();
  data.busVoltage_V = ina226.getBusVoltage_V();
  data.loadVoltage_V = data.busVoltage_V+ (data.shuntVoltage_mV/1000.0);
  data.current_mA = ina226.getCurrent_mA();
  data.power_mW = ina226.getBusPower();
  data.overflow = ina226.overflow;
  Serial.println(data.overflow ? "Overflow! Choose higher current range" : "Values OK - no overflow");
  return data;
}



