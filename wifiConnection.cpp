#include "wifiConnection.h"

void wifiConnection(const char* ssid,const char* pass){
  WiFi.begin(ssid,pass);
  
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }

  Serial.println();
  Serial.print("connected to wifi");
}

