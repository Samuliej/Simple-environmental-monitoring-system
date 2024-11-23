#ifndef MqttClient_h
#define MqttClient_h

#include <PubSubClient.h>
#include <WiFi.h>

// Class for establishing and maintaining an MQTT connection
class MqttClient {
    private:
        // Object representing the MQTT client, used for establishing and maintaining the connection
        PubSubClient client;  
        const char* clientID;

    public:
        // Constructor that takes a reference to a WiFiClient object to establish
        // a connection to the MQTT client.
        // The server is received as a pointer to a string, which is used as the address
        // to which the client connects
        MqttClient(WiFiClient& wifiClient, const char* server);

        // Subroutine that takes a pointer to a string as a parameter,
        // representing the client ID used to log in to the connection
        void connect(const char* clientID);

        // Subroutine for reconnecting to the connection
        void reconnect();

        // Template subroutine that publishes a value to the MQTT server
        // to the given topic
        // Parameters:
        //      topic: The topic to which the value is published.
        //      value: The value, of generic type T, that is published.
        //      format: The format in which the value is desired
        template <typename T>
        void publish(const char* topic, T value, const char* format) {
            if (topic == nullptr || format == nullptr) {
                Serial.println("Error: Topic or format is null");
                return;
            }

            // Convert string for printing
            String topicToPrint = String(topic);
            topicToPrint = topicToPrint.substring(topicToPrint.lastIndexOf("/") + 1);

            Serial.println("Publishing to topic: " + topicToPrint);

            if (!client.connected()) {
                Serial.println("Client not connected");
                reconnect();
            }

            char msg[80];
            sprintf(msg, format, value);
            // Potential issue, as the conditional statement waits for what publish returns.
            if (client.publish(topic, msg)) {
                Serial.println("Published to topic: " + topicToPrint);
            } else {
                Serial.println("Error publishing to topic: " + topicToPrint);
            }
        }

        // Subroutine to keep the connection alive
        void loop();

        // Subroutine to check if the MQTT connection is established
        bool connected();
};

#endif