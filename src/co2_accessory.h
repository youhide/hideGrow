#ifndef CO2_ACCESSORY_H
#define CO2_ACCESSORY_H

#include "HomeSpan.h"
#include <MHZ19.h>

#define CO2_RX_PIN 16  // GPIO16 for UART2 RX
#define CO2_TX_PIN 17  // GPIO17 for UART2 TX

struct CO2Sensor : Service::CarbonDioxideSensor {
  SpanCharacteristic *carbonDioxideLevel;
  SpanCharacteristic *carbonDioxideDetected;
  MHZ19 mhz19;
  
  CO2Sensor() : Service::CarbonDioxideSensor() {
    Serial2.begin(9600, SERIAL_8N1, CO2_RX_PIN, CO2_TX_PIN);
    mhz19.begin(Serial2);
    
    carbonDioxideLevel = new Characteristic::CarbonDioxideLevel(0);
    carbonDioxideDetected = new Characteristic::CarbonDioxideDetected(0);
    
    delay(2000); // Sensor warmup
  }

  void loop() {
    int co2 = mhz19.getCO2();
    
    if (co2 > 0) {
      carbonDioxideLevel->setVal(co2);
      carbonDioxideDetected->setVal(co2 > 1000 ? 1 : 0);
      delay(5000);
    }
  }
};

#endif
