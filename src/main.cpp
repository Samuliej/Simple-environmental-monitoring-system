#include <JsonFetcher.h>
#include <AlarmController.h>
#include <CityDataFetcher.h>
#include <MqttClient.h>
#include <SensorManager.h>

// Interval for data posting
#define TIME_POST_DATA 300000 // In "milliseconds"
unsigned long lastTime = 0;   // initialize

// Wi-Fi network details
const char* ssid = "";     // WiFi SSID
const char* password = ""; // password, if in use
const String API_KEY = ""; // OpenWeatherin API key

// City for which temperature is fetched
const String city = "Jyväskylä";

// Coordinates for which air quality is fetched
const String latitude = "62.23";
const String longitude = "25.73";

// Object for fetching city weather data
CityDataFetcher cityDataFetcher;


// MQTT-broker's details
const char* mqtt_server         = "broker.address.com"; 
const char* clientID            = "your.id.here";                     
const char* tempTopic           = "your/topic/address/RoomTemperature";
const char* humidTopic          = "your/topic/address/RoomHumidity";
const char* luxTopic            = "your/topic/address/RoomLUX";
const char* cityTempTopic       = "your/topic/address/City_Temperature";  
const char* cityAirDustTopic    = "your/topic/address/City_AirDustContent";
const char* cityAirNo2Topic     = "your/topic/address/City_AirNo2Content";
const char* alarmTopic          = "your/topic/address/alarm";

// Objects required for MQTT communication
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient, mqtt_server);

// Object managing sensors
SensorManager sensorManager;

// Other variables
int led = 4;
int Button1 = 35;
bool clearingAlarm = false;

// Object managing alarms
AlarmController alarmController(led);

// Function declarations
void setup_wifi();
void ISRClearAlarm();
void handleEngageAlarm();
void handleDisengageAlarm();
void handleWeatherMeasurementsAndPublish();


void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup.");
  while(!Serial) delay(10);

  pinMode(led, OUTPUT);         // sets the digital pin as output
  pinMode(Button1, INPUT);      // sets the digital pin as input
  digitalWrite(led, LOW);       // Initially turn off the LED. AlarmController handles the rest
 
  attachInterrupt(digitalPinToInterrupt(Button1), ISRClearAlarm, RISING);  // Attach interrupt to Button1

  // Halt the program if any values are missing
  if (city == "" || API_KEY == "" || latitude == "" || longitude == "") {
    Serial.println("Value or values missing: \n City: " + city + "\n API key: " + API_KEY + "\n Latitude: " + latitude + "\n Longitude: " + longitude);
    while (1);
  } else {
    // API URLs
    String cityWeatherUrl    = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&units=metric&appid=" + API_KEY;
    String cityAirQualityUrl = "https://api.openweathermap.org/data/2.5/air_pollution?lat=" + latitude + "&lon=" + longitude + "&appid=" + API_KEY;
    cityDataFetcher.setWeatherUrl(cityWeatherUrl);
    cityDataFetcher.setAirQualityUrl(cityAirQualityUrl);
  }

  setup_wifi();  // Call WiFi setup function

  // Initialize MQTT communication
  mqttClient.connect(clientID);

  // Initialize sensors
  sensorManager.initialize();

  // Start counting time for data posting
  lastTime = millis();

  Serial.println("Setup complete.");
}


void loop() {
  mqttClient.loop();   // Keep MQTT connection alive

  sensorManager.measureAcceleration(); // Measure acceleration
  if (sensorManager.acc > 2.5 && alarmController.getStatus() == 0) handleEngageAlarm();  // Trigger the alarm if acceleration over a fixed boundary

  if (clearingAlarm) handleDisengageAlarm();   // Clear alarm if ISR flipped the flag

  if ((millis() - lastTime) > TIME_POST_DATA) {  // Check if it's time to post data
    if (!mqttClient.connected()) {
      mqttClient.reconnect();
    }

    handleWeatherMeasurementsAndPublish();  // Perform weather measurements and publish

    lastTime = millis();      // Record the elapsed time
  }
}



/*               SUBROUTINES               */

// Subroutine for measuring room temperature and humidity
// and fetching weather data from the cloud
void handleWeatherMeasurementsAndPublish() {
    // Measure temperature and humidity and send to the cloud
    sensorManager.measureTemperatureAndHumidity();
    mqttClient.publish(tempTopic, sensorManager.temperature, "%.1f");
    mqttClient.publish(humidTopic, sensorManager.humidity, "%d");

    // Measure luminosity and send to the cloud
    sensorManager.measureLuminosity();
    mqttClient.publish(luxTopic, sensorManager.lux, "%d");

    // Fetch city temperature and send to the cloud
    cityDataFetcher.fetchWeather();
    mqttClient.publish(cityTempTopic, cityDataFetcher.cityTemperature, "%.1f");

    // Fetch city dust and NO2 levels and send to the cloud
    cityDataFetcher.fetchAirQuality();
    mqttClient.publish(cityAirDustTopic, cityDataFetcher.cityPm2_5, "%.1f");
    mqttClient.publish(cityAirNo2Topic, cityDataFetcher.cityNo2, "%.1f");

    Serial.println("*****************************************");
}


// Subroutine for engaging the alarm and publishing the status
void handleEngageAlarm() {
  alarmController.engageAlarm();
  mqttClient.publish(alarmTopic, alarmController.getStatus(), "%d");
  Serial.println("*****************************************");
  delay(50);
}


// Subroutine for disengaging the alarm and publishing the status
void handleDisengageAlarm() {
  alarmController.disengageAlarm();
  mqttClient.publish(alarmTopic, alarmController.getStatus(), "%d");
  Serial.println("*****************************************");
  clearingAlarm = false;
  delay(50);
}


// ISR for clearing the alarm
void ISRClearAlarm() {
  if (alarmController.getStatus() == 1 && !clearingAlarm) {
    clearingAlarm = true;
  }
}


// Subroutine for connecting to the WiFi network
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi"); 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("Connected");
}