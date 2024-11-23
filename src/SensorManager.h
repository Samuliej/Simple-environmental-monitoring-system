#ifndef SensorManager_h
#define SensorManager_h

#include "Adafruit_TSL2591.h"
#include "Adafruit_SHTC3.h"
#include <Adafruit_LIS331HH.h>

// Class for managing sensors and the data they measure
class SensorManager {
    private:
        Adafruit_TSL2591 tsl;   // Create measurement objects
        Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
        Adafruit_LIS331HH lis = Adafruit_LIS331HH();
        const float DIVIDE_VAL = 29.43;

    public:
        float temperature;  // Variables for storing values
        int humidity;
        uint16_t lux;
        float acc;

        // Constructor
        SensorManager();

        // Subroutine for initializing sensors
        void initialize();

        // Subroutine for measuring temperature and humidity with the sensor
        void measureTemperatureAndHumidity();

        // Subroutine for measuring luminosity
        void measureLuminosity();

        // Subroutine for measuring acceleration
        void measureAcceleration();
};

#endif