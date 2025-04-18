#define BLYNK_TEMPLATE_ID "TMPL3C-B-3N2V"
#define BLYNK_TEMPLATE_NAME "IoT Enable Solar Tracking System"
#define BLYNK_AUTH_TOKEN "_gDiltngBrVsI1t4cG8cduavXtdPwkWu"
#include <BlynkSimpleEsp32.h>  
#include "sendToBlynk.h" 

void initBlynk(const char* auth, const char* ssid, const char* pass) {
  Blynk.begin(auth, ssid, pass);
}

void sendToBlynk() {
  INA226Data sensorData = getINA226Value();
  Blynk.virtualWrite(V0, sensorData.shuntVoltage_mV);
  Blynk.virtualWrite(V1, sensorData.busVoltage_V);
  Blynk.virtualWrite(V2, sensorData.loadVoltage_V);
  Blynk.virtualWrite(V3, sensorData.current_mA);
  Blynk.virtualWrite(V4, sensorData.power_mW);
  Blynk.run();
}
