#include "esp32_server.h"
#include "pins.h"
#include "adc_battery.h"
#include "wifi.h"

#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const char* AP_SSID_PREFIX = "ESP32_TeddyBear_";
String ap_ssid;

// Funciones de manejo de solicitudes HTTP
void handleRoot();
void handleGetBatteryLevel();
void handleGetMACAddress();
void handleSetWiFiCredentials();

void startAPMode() {
  // Generar SSID del AP usando la dirección MAC
  String mac = getMACAddress();
  mac.replace(":", "");
  ap_ssid = String(AP_SSID_PREFIX) + mac.substring(6); // Usar los últimos 6 caracteres

  // Configurar WiFi en modo AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid.c_str());
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP SSID: ");
  Serial.println(ap_ssid);
  Serial.print("Dirección IP del AP: ");
  Serial.println(IP);

  // Definir rutas del servidor
  server.on("/", HTTP_GET, handleRoot);
  server.on("/getBatteryLevel", HTTP_GET, handleGetBatteryLevel);
  server.on("/getMACAddress", HTTP_GET, handleGetMACAddress);
  server.on("/setWiFiCredentials", HTTP_POST, handleSetWiFiCredentials);

  // Iniciar el servidor HTTP
  server.begin();
  Serial.println("Servidor HTTP iniciado en modo AP.");
}

void stopAPMode() {
  server.stop();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_OFF);
  Serial.println("Modo AP detenido y servidor HTTP detenido.");
}

void handleClientRequests() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Servidor ESP32 Teddy Bear");
}

void handleGetBatteryLevel() {
  uint8_t batteryLevel = readBatteryLevel();
  String response = String(batteryLevel);
  server.send(200, "text/plain", response);
}

void handleGetMACAddress() {
  String mac = getMACAddress();
  server.send(200, "text/plain", mac);
}

void handleSetWiFiCredentials() {
  if (server.hasArg("ssid") && server.hasArg("password")) {
    String ssid = server.arg("ssid");
    String password = server.arg("password");

    // Guardar credenciales
    saveWiFiCredentials(ssid.c_str(), password.c_str());

    server.send(200, "text/plain", "Credenciales recibidas y guardadas. Reiniciando para conectar a WiFi.");

    Serial.println("Credenciales de WiFi recibidas vía HTTP POST:");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Contraseña: ");
    Serial.println(password);

    // Reiniciar el ESP32 para conectar a WiFi
    ESP.restart();
  } else {
    server.send(400, "text/plain", "Faltan los parámetros 'ssid' o 'password'.");
  }
}
