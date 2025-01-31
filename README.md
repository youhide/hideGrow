# hideGrow Sensor Hub

ESP32-based environmental monitoring system with HomeKit integration for pH, temperature, and CO2 measurements.

## Hardware Requirements

- ESP32 development board
- ADS1115 16-bit ADC
- SEN0161 pH sensor (analog output)
- DS18B20 temperature sensor (analog output)
- MH-Z19B CO2 sensor (UART interface)

## Dependencies

- HomeSpan library
- Wire library (built-in)
- Adafruit_ADS1X15 library
- MH-Z19 library (version 1.5.4 or higher)
- PlatformIO for development

## Pin Configuration

| Component | Pin/Interface |
|-----------|--------------|
| ADS1115 | I2C (SDA: GPIO21, SCL: GPIO22) |
| pH Sensor | ADS1115 A0 |
| Temperature Sensor | ADS1115 A1 |
| CO2 Sensor | UART (RX: GPIO16, TX: GPIO17) |

## Features

- High precision 16-bit ADC readings using ADS1115
- Real-time pH monitoring (0-14 range)
- Temperature monitoring (-50°C to 100°C)
- CO2 monitoring (400-5000ppm)
- HomeKit integration
- Automatic value updates every 5 seconds

## HomeKit Integration

The device appears as three sensors:
1. pH Sensor (shown as Light Sensor, range 0-14)
2. Temperature Sensor (range -50°C to 100°C)
3. CO2 Sensor (range 400-5000ppm)

## License

MIT License - See LICENSE file for details
