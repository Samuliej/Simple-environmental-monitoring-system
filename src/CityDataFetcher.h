#ifndef CityDataFetcher_h
#define CityDataFetcher_h

#include <JsonFetcher.h>
#include <stdio.h>

// Class for fetching weather data of a desired city via API
class CityDataFetcher {
    private:
        JsonFetcher jsonFetcher;  // Object for fetching JSON data from a web address
        String weatherUrl;        // API URL for fetching city weather data
        String airQualityUrl;     // API URL for fetching city air quality data

    public:
        float cityTemperature;    // City temperature in degrees
        float cityPm2_5;          // City air dust content
        float cityNo2;            // City air nitrogen dioxide content

        CityDataFetcher() {};

        // Constructor that takes URLs for fetching city weather data
        CityDataFetcher(const String& weather, const String& airQuality);

        void setWeatherUrl(const String& url);
        void setAirQualityUrl(const String& url);

        // Subroutine for fetching weather data
        void fetchWeather();

        // Subroutine for fetching air quality data
        void fetchAirQuality();
};

#endif