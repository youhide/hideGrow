#ifndef TEMPERATURE_ACCESSORY_H
#define TEMPERATURE_ACCESSORY_H

#include "HomeSpan.h"
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

struct TempSensor : Service::TemperatureSensor {
  SpanCharacteristic *currentTemp;
  Adafruit_ADS1115 ads;
  const float VOLTAGE_RANGE = 4.096;
  const float ADC_RESOLUTION = 32767.0;
  
  TempSensor() : Service::TemperatureSensor() {
    ads.begin();
    ads.setGain(GAIN_ONE);
    
    currentTemp = new Characteristic::CurrentTemperature(20);
    currentTemp->setRange(-50, 100);
  }

  float readTemperature() {
    int16_t adc = ads.readADC_SingleEnded(1); // Read from A1
    float voltage = (adc * VOLTAGE_RANGE) / ADC_RESOLUTION;
    // Convert voltage to temperature (adjust formula based on your sensor)
    float tempC = (voltage - 0.5) * 100.0; // Example conversion for LM35
    return constrain(tempC, -50, 100);
  }

  void loop() {
    float tempC = readTemperature();
    if(abs(currentTemp->getVal<float>() - tempC) > 0.5) {
      currentTemp->setVal(tempC);
      delay(5000);
    }
  }
};

#endif
