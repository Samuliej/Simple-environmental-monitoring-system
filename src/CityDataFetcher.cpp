#include <CityDataFetcher.h>

// Constructor that takes URLs for fetching city weather data
CityDataFetcher::CityDataFetcher(const String& weather, const String& airQuality)
    : weatherUrl(weather), airQualityUrl(airQuality) {}

// Subroutine for fetching weather data
void CityDataFetcher::fetchWeather() {
    JsonDocument jsonDoc;
    if (jsonFetcher.fetchJson(weatherUrl, jsonDoc)) {
        cityTemperature = jsonDoc["main"]["temp"].as<float>();
    }
}

// Subroutine for fetching air quality data
void CityDataFetcher::fetchAirQuality() {
    JsonDocument jsonDoc;
    if (jsonFetcher.fetchJson(airQualityUrl, jsonDoc)) {
        cityPm2_5 = jsonDoc["list"][0]["components"]["pm2_5"].as<float>();
        cityNo2 = jsonDoc["list"][0]["components"]["no2"].as<float>();
    }
}

void CityDataFetcher::setWeatherUrl(const String& url) {
    weatherUrl = url;
}

void CityDataFetcher::setAirQualityUrl(const String& url) {
    airQualityUrl = url;
}