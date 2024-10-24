// wifi.cpp
#include "wifi.h"
#include <WiFi.h>
#include "config.h"

// Configura las credenciales WiFi
const char* ssid = WIFI_SSID; // Cambia esto por tu SSID
const char* password = WIFI_PASSWORD; // Cambia esto por tu contraseña

void initWiFi() {
    // Inicializar WiFi
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Conectado.");
}

