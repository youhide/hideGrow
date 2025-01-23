# hideGrow Sensor Hub

ESP32-based environmental monitoring system with HomeKit integration for pH, temperature, and CO2 measurements.

## Hardware Requirements

- ESP32 development board
- pH sensor (I2C interface)
- DS18B20 temperature sensor (I2C interface)
- MH-Z19B CO2 sensor (UART interface)

## Dependencies

- HomeSpan library
- Wire library (built-in)
- MH-Z19 library (version 1.5.4 or higher)
- PlatformIO for development

## Pin Configuration

| Sensor | Pin/Interface |
|--------|--------------|
| pH Sensor | I2C (SDA: GPIO21, SCL: GPIO22) |
| Temperature Sensor | I2C (shared with pH sensor) |
| CO2 Sensor | UART (RX: GPIO16, TX: GPIO17) |

## Installation

1. Clone the repository
2. Open project in VSCode with PlatformIO extension
3. Install dependencies through PlatformIO
4. Upload to ESP32

## Usage

1. Power up the ESP32
2. Add accessory to HomeKit:
    - Open Home app
    - Add accessory
    - Scan code provided by device
    - Follow pairing instructions

## Features

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
