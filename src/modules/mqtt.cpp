#include "mqtt.h"
#include "config.h"
#include <PubSubClient.h>
#include <WiFi.h>

// Variables globales
WiFiClient wifiClient; // Crear cliente WiFi
PubSubClient mqttClient(wifiClient); // Crear cliente MQTT

void initMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT); // Establecer el servidor y el puerto
    Serial.println("MQTT inicializado.");
}

void maintainMQTT() {
    if (!mqttClient.connected()) {
        Serial.println("Reconectando a MQTT...");
        // Intenta reconectar
        if (mqttClient.connect("AI_Teddy_Bear_Client")) {
            Serial.println("Conectado a MQTT.");
        } else {
            Serial.print("Fallo de conexión, código de error: ");
            Serial.print(mqttClient.state());
            delay(2000);
        }
    }
    mqttClient.loop(); // Mantener la conexión MQTT
}

