#ifndef JsonFetcher_h
#define JsonFetcher_h

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <stdio.h>

// Class representing an object that can fetch a string from a URL
// and parse it into a JSON document
class JsonFetcher {
    private:
        HTTPClient http;  // Object for establishing HTTP connection and fetching data

    public:
        // Constructor
        JsonFetcher();

        // Fetch a string from the URL, parse it into the given JSON document
        // Returns true if successful, false if either parsing or HTTP GET fails
        bool fetchJson(const String& url, JsonDocument& jsonDoc);
};

#endif