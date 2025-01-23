#ifndef TEMPERATURE_ACCESSORY_H
#define TEMPERATURE_ACCESSORY_H

#include "HomeSpan.h"
#include <Wire.h>

#define DS18B20_I2C_ADDRESS 0x48  // Default I2C address for DS18B20

struct TempSensor : Service::TemperatureSensor {
  SpanCharacteristic *currentTemp;
  
  TempSensor() : Service::TemperatureSensor() {
    Wire.begin();
    currentTemp = new Characteristic::CurrentTemperature(0);
    currentTemp->setRange(-50, 100);
  }

  float readTemperature() {
    Wire.beginTransmission(DS18B20_I2C_ADDRESS);
    Wire.write(0x00);  // Temperature register
    Wire.endTransmission();
    
    Wire.requestFrom(DS18B20_I2C_ADDRESS, 2);
    if(Wire.available() >= 2) {
      int16_t temp = (Wire.read() << 8) | Wire.read();
      return temp * 0.0625;  // Convert to Celsius
    }
    return -273;  // Error value
  }

  void loop() {
    float tempC = readTemperature();
    if(tempC > -273 && abs(currentTemp->getVal<float>() - tempC) > 0.5) {
      currentTemp->setVal(tempC);
      delay(5000);
    }
  }
};

#endif
