// otaManager.cpp
#include "otaManager.h"
#include <ArduinoOTA.h>

void setupOTA() {
  ArduinoOTA
    .onStart([]() {
      // Optional: do something when OTA starts
    })
    .onEnd([]() {
      // Optional: do something when OTA ends
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      // Optional: track OTA progress
    })
    .onError([](ota_error_t error) {
      // Optional: handle OTA errors
    });

  ArduinoOTA.begin();
}

void handleOTA() {
  ArduinoOTA.handle();
}
