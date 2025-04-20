#define BLYNK_TEMPLATE_ID "TMPL3C-B-3N2V"
#define BLYNK_TEMPLATE_NAME "IoT Enable Solar Tracking System"
#define BLYNK_AUTH_TOKEN "_gDiltngBrVsI1t4cG8cduavXtdPwkWun"

#include <BlynkSimpleEsp32.h>  
#include <WiFi.h>
#include "sendToBlynk.h" 

// Timing variables
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 12000; // this value is in milliseconds 1 sec=1000 ms

void initWiFiAndBlynk(const char* auth, const char* ssid, const char* pass) {
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
}

void sendToBlynk() {
  Blynk.run(); 
  //interval
  unsigned long currentMillis = millis();
  if (currentMillis - lastSendTime >= sendInterval) {
    lastSendTime = currentMillis;

    INA226Data sensorData = getINA226Value();
    Blynk.virtualWrite(V0, sensorData.shuntVoltage_mV);
    Blynk.virtualWrite(V1, sensorData.busVoltage_V);
    Blynk.virtualWrite(V2, sensorData.loadVoltage_V);
    Blynk.virtualWrite(V3, sensorData.current_mA);
    Blynk.virtualWrite(V4, sensorData.power_mW);
  }
}
