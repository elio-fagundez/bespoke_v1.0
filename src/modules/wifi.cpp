#include "wifi.h"
#include "config.h"

Preferences preferences;

// Claves para almacenar las credenciales en NVS
const char* WIFI_SSID_KEY = "wifi_ssid";
const char* WIFI_PASS_KEY = "wifi_pass";
const char* WIFI_NAMESPACE = "wifi_creds";
// Define el tiempo límite de conexión en milisegundos
const unsigned long WIFI_CONNECT_TIMEOUT = 10000;  // 10 segundos
void initWiFi() {
  // Configurar WiFi en modo estación
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("WiFi inicializado en modo estación.");
}

bool connectToWiFi() {
  char ssid[32];
  char password[64];

  // Cargar credenciales almacenadas
  if (!loadWiFiCredentials(ssid, password, sizeof(ssid))) {
    Serial.println("No se encontraron credenciales de WiFi.");
    return false;
  }

  // Intentar conectar a WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi SSID: ");
  Serial.println(ssid);

  unsigned long startAttemptTime = millis();

  // Esperar hasta que se conecte o se agote el tiempo
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_CONNECT_TIMEOUT) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n¡Conectado a WiFi!");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("\nNo se pudo conectar a WiFi.");
    return false;
  }
}

void saveWiFiCredentials(const char* ssid, const char* password) {
  // Guardar credenciales en NVS
  preferences.begin(WIFI_NAMESPACE, false);
  preferences.putString(WIFI_SSID_KEY, ssid);
  preferences.putString(WIFI_PASS_KEY, password);
  preferences.end();
  Serial.println("Credenciales de WiFi guardadas.");
}

bool loadWiFiCredentials(char* ssid, char* password, size_t maxLength) {
  // Cargar credenciales desde NVS
  preferences.begin(WIFI_NAMESPACE, true); // Modo solo lectura
  String stored_ssid = preferences.getString(WIFI_SSID_KEY, "");
  String stored_pass = preferences.getString(WIFI_PASS_KEY, "");
  preferences.end();

  if (stored_ssid.length() == 0 || stored_pass.length() == 0) {
    return false;
  } else {
    stored_ssid.toCharArray(ssid, maxLength);
    stored_pass.toCharArray(password, maxLength);
    return true;
  }
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

String getMACAddress() {
  return WiFi.macAddress();
}

void disconnectWiFi() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  Serial.println("Desconectado de WiFi y módulo WiFi apagado.");
}



