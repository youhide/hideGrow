#include "HomeSpan.h"

struct PHSensor : Service::LightSensor {
  SpanCharacteristic *currentPH;
  int sensorPin;
  
  PHSensor(int pin) : Service::LightSensor() {
    sensorPin = pin;
    currentPH = new Characteristic::CurrentAmbientLightLevel(0);
    currentPH->setRange(0, 14); // pH range 0-14
  }

  void loop() {
    // Read pH sensor value
    float voltage = analogRead(sensorPin) * (3.3 / 4095.0);
    float phValue = 3.5 * voltage; // Convert voltage to pH (calibration needed)
    
    // Update characteristic if value changed
    if(abs(currentPH->getVal<float>() - phValue) > 0.1) {
      currentPH->setVal(phValue);
      delay(5000); // Update every 5 seconds
    }
  }
};
