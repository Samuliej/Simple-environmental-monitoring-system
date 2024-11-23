#include <SensorManager.h>

// Constructor
SensorManager::SensorManager(): tsl(2591) {}

// Subroutine for initializing sensors
void SensorManager::initialize() {

    // TSL2591
    if (!tsl.begin()) {
        Serial.println("TSL sensor not found");
        while (1);
    }

    Serial.println("TSL found!");

    // SHTC3
    if (!shtc3.begin()) {
        Serial.println("SHTC3 sensor not found");
        while(1);
    }

    Serial.println("SHTC3 found!");

    // LIS331HH
    if (!lis.begin_I2C()) {
        Serial.println("Couldn't start!");
        while (1) yield();
    } 

    Serial.println("LIS331HH found!");

    Serial.println("Configuring sensors...");

    tsl.setGain(TSL2591_GAIN_MED);
    tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);

    lis.setRange(LIS331HH_RANGE_6_G);   // 6, 12, or 24 G
    lis.setDataRate(LIS331_DATARATE_1000_HZ);  // 50, 100, 400 or 1000 Hz

    Serial.println("Sensor configuration complete.");
}

// Subroutine for measuring temperature and humidity with the sensor
void SensorManager::measureTemperatureAndHumidity() {
    sensors_event_t humidityEvent, temperatureEvent;
    shtc3.getEvent(&humidityEvent, &temperatureEvent);

    temperature = temperatureEvent.temperature;
    humidity = static_cast<int>(humidityEvent.relative_humidity);
}

// Subroutine for measuring luminosity
void SensorManager::measureLuminosity() {
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir = lum >> 16;
    uint16_t full = lum & 0xFFFF;

    lux = static_cast<uint16_t>(tsl.calculateLux(full, ir));
}

// Subroutine for measuring acceleration
void SensorManager::measureAcceleration() {
    sensors_event_t event;
    lis.getEvent(&event);

    // pow is usually a costly operation so normal multiplication is used
    float acc = sqrt(
                (event.acceleration.x * event.acceleration.x) +
                (event.acceleration.y * event.acceleration.y) +
                (event.acceleration.z * event.acceleration.z)
            ) / DIVIDE_VAL;

    this->acc = acc;
}