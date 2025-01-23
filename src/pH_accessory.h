#ifndef PH_ACCESSORY_H
#define PH_ACCESSORY_H

#include "HomeSpan.h"
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

struct PHSensor : Service::LightSensor {
  SpanCharacteristic *currentPH;
  Adafruit_ADS1115 ads;
  const float VOLTAGE_RANGE = 4.096; // ADS1115 FSR in volts
  const float ADC_RESOLUTION = 32767.0; // 15-bit resolution
  
  PHSensor() : Service::LightSensor() {
    ads.begin();
    ads.setGain(GAIN_ONE); // Set FSR to ±4.096V
    
    currentPH = new Characteristic::CurrentAmbientLightLevel(7.0);
    currentPH->setRange(0, 14);
  }

  float readPH() {
    int16_t adc = ads.readADC_SingleEnded(0); // Read from A0
    float voltage = (adc * VOLTAGE_RANGE) / ADC_RESOLUTION;
    // Convert voltage to pH (you'll need to calibrate these values)
    float pH = 7.0 - ((2.5 - voltage) / 0.18); // Example conversion
    return constrain(pH, 0, 14);
  }

  void loop() {
    float pH = readPH();
    if(abs(currentPH->getVal<float>() - pH) > 0.1) {
      currentPH->setVal(pH);
      delay(5000);
    }
  }
};

#endif
