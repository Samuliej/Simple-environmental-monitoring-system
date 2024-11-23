# University Assignment: Simple IoT Environmental Monitoring System

This project is an IoT-based environmental monitoring system developed for a university assignment. The system collects data from various sensors, processes the data, and publishes it to an MQTT broker. The data includes room temperature, humidity, luminosity and acceleration. Additionally city weather, and air quality information are fetched from OpenWeather API via an API key that you need to provide. Creating an account is free at https://openweathermap.org.

## Overview

### Sensors and Data Collection

The system uses the following sensors:
- **TSL2591**: Measures luminosity.
- **SHTC3**: Measures temperature and humidity.
- **LIS331HH**: Measures acceleration.

The `SensorManager` class ([`src/SensorManager.h`](src/SensorManager.h)) is responsible for initializing and managing these sensors. It provides methods to measure temperature, humidity, luminosity, and acceleration.

### Data Fetching

The system fetches city weather and air quality data using the OpenWeatherMap API. The `CityDataFetcher` class ([`src/CityDataFetcher.h`](src/CityDataFetcher.h)) handles this functionality. It uses the `JsonFetcher` class ([`src/JsonFetcher.h`](src/JsonFetcher.h)) to perform HTTP GET requests and parse the JSON responses.

### MQTT Communication

The system publishes the collected data to an MQTT broker. The `MqttClient` class ([`src/MqttClient.h`](src/MqttClient.h)) manages the MQTT connection and provides methods to publish data to specific topics.

### Alarm System

An alarm system is implemented to trigger an alarm based on certain conditions (e.g., high acceleration). The `AlarmController` class ([`src/AlarmController.h`](src/AlarmController.h)) manages the alarm state and controls an LED to indicate the alarm status.

### Main Program

The main program ([`src/main.cpp`](src/main.cpp)) initializes the sensors, sets up the WiFi and MQTT connections, and periodically collects and publishes data. It also handles the alarm system based on sensor readings.

## Dependencies

The project uses the following libraries:
- `Adafruit TSL2591 Library`
- `Adafruit SHTC3 Library`
- `Adafruit LIS331HH`
- `ArduinoJson`
- `PubSubClient`
- `AsyncMqttClient`

These dependencies are specified in the `platformio.ini` file.

## Setup and Usage

You will need an dfrobot esp32-e board for testing this project and 
above mentioned sensors attached to it for the room measurements 
and alarm to work.

1. **Clone the repository**
2. **Open the project in PlatformIO**
3. **Configure the WiFi and API details in main.cpp**
4. **Build and upload the project to your microcontroller**
5. **Monitor the serial output to see the sensor readings and MQTT publish status**