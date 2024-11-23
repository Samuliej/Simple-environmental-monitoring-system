#include <MqttClient.h>

// Constructor that takes a reference to a WiFiClient object to establish
// a connection to the MQTT client.
// The server is received as a pointer to a string, which is used as the address
// to which the client connects
MqttClient::MqttClient(WiFiClient& wifiClient, const char* server): client(wifiClient) {
    client.setServer(server, 1883);
}

// Subroutine that takes a pointer to a string as a parameter,
// representing the client ID used to "log in" to the connection
void MqttClient::connect(const char* clientID) {
    Serial.println("Connecting MQTT...");
    if (!client.connected() && client.connect(clientID)) {
        this->clientID = clientID;  // Save clientID for reconnect
        Serial.println("MQTT connected");
    } else {
        Serial.println("MQTT connect failed");
    }
}

// Subroutine for reconnecting to the connection
void MqttClient::reconnect() {
    if (!client.connected() && client.connect(this->clientID)) {
        Serial.println("MQTT reconnected");
    } else {
        Serial.println("MQTT reconnect failed");
    }
}

// Subroutine to keep the connection alive
void MqttClient::loop() {
    client.loop();
}

// Subroutine to check if the MQTT connection is established
bool MqttClient::connected() {
    return client.connected();
}