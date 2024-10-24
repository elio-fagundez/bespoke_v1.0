// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Configuraciones globales del proyecto

// Constantes generales del proyecto
const unsigned long BAUD_RATE = 115200; // Velocidad de comunicación serial

// Configuración del servidor MQTT
#define MQTT_SERVER "broker.hivemq.com" // Cambia esto por tu servidor MQTT
#define MQTT_PORT 1883 // Cambia el puerto si es necesario

// Configuración de otros parámetros
#define MQTT_TOPIC "your/topic" // Cambia esto por tu tema MQTT

// Otras configuraciones
#define WIFI_SSID "your_wifi_ssid" // Cambia por tu SSID
#define WIFI_PASSWORD "your_wifi_password" // Cambia por tu contraseña

// Configuraciones de BLE

#define BLE_DEVICE_NAME "AI_Teddy_Bear"

// Otras configuraciones globales que puedas necesitar

#endif // CONFIG_H
