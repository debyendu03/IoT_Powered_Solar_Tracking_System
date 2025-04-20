#define BLYNK_TEMPLATE_ID "TMPL3Y95Jqa3r"
#define BLYNK_TEMPLATE_NAME "IoT Powered Solar Tracking System"
#define BLYNK_AUTH_TOKEN "UYV1OePmeVDxN0oYqXjUAJMCcVhza4iz"

#include <BlynkSimpleEsp32.h>  
#include <WiFi.h>
#include "sendToBlynk.h" 

unsigned long lastSendTime = 0;
unsigned long sendInterval = 60000; // Default interval: 1 minute (60000 milliseconds)

BLYNK_WRITE(V6) {
  int intervalValue = param.asInt(); 
  sendInterval = intervalValue * 60000; 

  if (sendInterval < 60000) { 
    sendInterval = 60000;
  }
  if (sendInterval > 3600000) {  
    sendInterval = 3600000;
  }
}

void initWiFiAndBlynk(const char* auth, const char* ssid, const char* pass) {
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
}

void sendToBlynk() {
  Blynk.run();  
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
