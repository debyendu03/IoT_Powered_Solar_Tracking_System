#ifndef SEND_TO_BLYNK_H
#define SEND_TO_BLYNK_H

#include "INA226Sensor.h"

 void initBlynk(const char* auth, const char* ssid, const char* pass);
 void sendToBlynk();

#endif
