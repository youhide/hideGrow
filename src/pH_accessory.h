#include "HomeSpan.h"
#include <Wire.h>

#define PH_I2C_ADDRESS 0x4D
#define PH_REG_VALUE 0x00

struct PHSensor : Service::LightSensor {
  SpanCharacteristic *currentPH;
  
  PHSensor() : Service::LightSensor() {
    Wire.begin();
    currentPH = new Characteristic::CurrentAmbientLightLevel(7.0); // Default neutral pH
    currentPH->setRange(0, 14);  // pH range 0-14
  }

  float readPH() {
    Wire.beginTransmission(PH_I2C_ADDRESS);
    Wire.write(PH_REG_VALUE);
    Wire.endTransmission();
    
    Wire.requestFrom(PH_I2C_ADDRESS, 2);
    if(Wire.available() >= 2) {
      uint16_t rawPH = (Wire.read() << 8) | Wire.read();
      return rawPH * 0.01;
    }
    return 7.0;
  }

  void loop() {
    float pH = readPH();
    if(abs(currentPH->getVal<float>() - pH) > 0.1) {
      currentPH->setVal(pH);
      delay(5000);
    }
  }
};
