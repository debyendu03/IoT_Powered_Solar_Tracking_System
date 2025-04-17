#ifndef INA226_SENSOR_H
#define INA226_SENSOR_H

typedef struct {
  float shuntVoltage_mV;
  float busVoltage_V;
  float loadVoltage_V;
  float current_mA;
  float power_mW;
  bool overflow;

}INA226Data;

void initINA226();
INA226Data getINA226Value();

#endif
