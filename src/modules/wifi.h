#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Preferences.h>

// Inicializa el módulo WiFi en modo estación
void initWiFi();

// Conecta a la red WiFi usando las credenciales almacenadas
bool connectToWiFi();

// Guarda las credenciales de WiFi en la memoria no volátil
void saveWiFiCredentials(const char* ssid, const char* password);

// Carga las credenciales de WiFi desde la memoria no volátil
bool loadWiFiCredentials(char* ssid, char* password, size_t maxLength);

// Verifica si el ESP32 está conectado a WiFi
bool isWiFiConnected();

// Obtiene la dirección MAC del ESP32
String getMACAddress();

// Desconecta el WiFi y apaga el módulo
void disconnectWiFi();

#endif // WIFI_H



