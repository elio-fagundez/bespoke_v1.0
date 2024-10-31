// wifi.cpp
#include "wifi.h"
#include <WiFi.h>
#include "config.h"

// Setting credentials  WiFi
const char* ssid = WIFI_SSID; 
const char* password = WIFI_PASSWORD; 

void initWiFi() {
    WiFi.begin(ssid, password);
    Serial.print("Conecting to WiFi...");
    waitForWiFiConnection();
}

void waitForWiFiConnection() {
    Serial.println("Waiting conection to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");
}


