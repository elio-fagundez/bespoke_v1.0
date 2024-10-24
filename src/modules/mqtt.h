// mqtt.h
#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>

// Inicializar MQTT
void initMQTT();

// Función para mantener la conexión MQTT
void maintainMQTT();

// Publicar un mensaje en un topic específico
void publishMessage(const char* topic, const char* message);

// Función de callback para manejar mensajes entrantes
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif // MQTT_H
