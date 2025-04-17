#include "INA226Sensor.h"  // Include header to match functions declared in .h
#include <Wire.h>
#include <INA226_WE.h>

#define I2C_ADDRESS 0x40
INA226_WE ina226(I2C_ADDRESS); 

// Your function definitions go here
void initINA226() {
  Wire.begin(21, 22);
  ina226.init();
  ina226.setResistorRange(0.1, 1.3); // 0.1 Ohm shunt, up to 1.3A
  ina226.setCorrectionFactor(0.93);
  ina226.waitUntilConversionCompleted(); // ensure first read isn't zero
  Serial.println("INA226 Initialized.");
}

INA226Data getINA226Value() {
  INA226Data data;
  data.shuntVoltage_mV = ina226.getShuntVoltage_mV();
  data.busVoltage_V = ina226.getBusVoltage_V();
  data.loadVoltage_V = data.busVoltage_V+ (data.shuntVoltage_mV/1000);
  data.current_mA = ina226.getCurrent_mA();
  data.power_mW = ina226.getBusPower();
  data.overflow = ina226.overflow;

  Serial.print("Shunt Voltage [mV]: "); Serial.println(data.shuntVoltage_mV, 6);
  Serial.print("Bus Voltage [V]: "); Serial.println(data.busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(data.loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(data.current_mA, 6);
  Serial.print("Bus Power [mW]: "); Serial.println(data.power_mW , 6);

  if (!ina226.overflow) {
    Serial.println("Values OK - no overflow");
  } else {
    Serial.println("Overflow! Choose higher current range");
  }

  Serial.println();
  
  return data;
}



/*
void getINA226Value() {
  float shuntVoltage_mV = ina226.getShuntVoltage_mV();
  float busVoltage_V = ina226.getBusVoltage_V();
  float current_mA = ina226.getCurrent_mA();
  float power_mW = ina226.getBusPower();
  float loadVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000);

  Serial.print("Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV, 6);
  Serial.print("Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(current_mA, 6);
  Serial.print("Bus Power [mW]: "); Serial.println(power_mW, 6);

  if (!ina226.overflow) {
    Serial.println("Values OK - no overflow");
  } else {
    Serial.println("Overflow! Choose higher current range");
  }

  Serial.println();
}
*/


