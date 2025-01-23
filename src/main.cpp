#include <Arduino.h>
#include "HomeSpan.h"
#include "pH_accessory.h"
#include "temperature_accessory.h"
#include "DNSServer.h"

void setup() {
  Serial.begin(115200);
  homeSpan.begin(Category::Sensors, "pH & Temperature Sensor");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Name("pH & Temperature Sensor");
      new Characteristic::Manufacturer("hideGrow");
      new Characteristic::SerialNumber("123-ABC");
      new Characteristic::Model("HG-SENSOR-001");
      new Characteristic::FirmwareRevision("1.0");
      new Characteristic::Identify();
      
    // Add pH sensor service
    new PHSensor();
    // Add temperature sensor service
    new TempSensor();
}

void loop() {
  homeSpan.poll();
}
