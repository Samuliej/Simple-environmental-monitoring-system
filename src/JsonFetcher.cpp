#include <JsonFetcher.h>

// Constructor
JsonFetcher::JsonFetcher() {}

// Fetch a string from the URL, parse it into the given JSON document
// Returns true if successful, false if either parsing or HTTP GET fails
bool JsonFetcher::fetchJson(const String& url, JsonDocument& jsonDoc) {
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
        String res = http.getString();
        DeserializationError error = deserializeJson(jsonDoc, res);
        if (error) {
            Serial.println("Error parsing JSON: " + String(error.c_str()));
            jsonDoc.clear();    // Clear jsonDoc object if parsing fails
            return false;
        }
    } else {
        Serial.println("Error sending request HTTP code: " + httpCode);
        jsonDoc.clear();       // Clear jsonDoc object if request fails
        return false;
    }

    // Release HTTP resources
    http.end();
    return true;
}