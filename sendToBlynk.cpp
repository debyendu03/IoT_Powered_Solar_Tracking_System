#define BLYNK_TEMPLATE_ID "TMPL3C-B-3N2V"
#define BLYNK_TEMPLATE_NAME "IoT Enable Solar Tracking System"
#define BLYNK_AUTH_TOKEN "_gDiltngBrVsI1t4cG8cduavXtdPwkWu"
#include <BlynkSimpleEsp32.h>  
#include "sendToBlynk.h" 

void initBlynk(const char* auth,const char* ssid,const char* pass){
   Blynk.begin(auth, ssid, pass);   // Blynk is already defined in the .ino file
}

void sendToBlynk() {
  INA226Data SensorData = getINA226Value();
  Blynk.virtualWrite(V0, SensorData.shuntVoltage_mV);
  Blynk.virtualWrite(V1, SensorData.busVoltage_V);
  Blynk.virtualWrite(V2, SensorData.loadVoltage_V);
  Blynk.virtualWrite(V3, SensorData.current_mA);
  Blynk.virtualWrite(V4, SensorData.power_mW);
  Blynk.run();
}
