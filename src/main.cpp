#include <Arduino.h>
#include "HomeSpan.h"
#include "pH_accessory.h"
#include "DNSServer.h"

#define PH_SENSOR_PIN 35 // Analog pin for pH sensor

void setup() {
  Serial.begin(115200);

  // Initialize HomeSpan
  homeSpan.begin(Category::Sensors, "pH Sensor");
  
  // Define the accessory
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Name("pH Sensor");
      new Characteristic::Manufacturer("hideGrow");
      new Characteristic::SerialNumber("123-ABC");
      new Characteristic::Model("HG-SENSOR-001");
      new Characteristic::FirmwareRevision("1.0");
      new Characteristic::Identify();
      
    // Add pH sensor service
    new PHSensor(PH_SENSOR_PIN);
}

void loop() {
  homeSpan.poll();
}
