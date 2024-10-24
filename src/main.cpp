// main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "pins.h"
#include "modules/ble.h"
#include "modules/mqtt.h"
#include "modules/wifi.h"
#include "modules/adc_battery.h"

// Declaración de funciones
void setup();
void loop();

// Configuración de variables globales
const int ledPowerOnPin = GPIO_POWER_ON;  // Pin para el LED de encendido
const int buttonVolUpPin = GPIO_BTN_VOL_UP; // Pin para botón de aumentar volumen
const int buttonVolDownPin = GPIO_BTN_VOL_DOWN; // Pin para botón de disminuir volumen

void setup() {
    // Configurar el pin del LED como salida
    pinMode(ledPowerOnPin, OUTPUT);
    digitalWrite(ledPowerOnPin, HIGH);  // Encender el LED

    // Inicializar Serial para depuración
    Serial.begin(115200);
    delay(1000);  // Esperar un segundo para que el puerto serie esté listo

    // Inicializar módulos
    initBLE();                   // Inicializar BLE
    initBatteryMeasurement();    // Inicializar medición de batería
    initMQTT();                 // Inicializar MQTT
    initWiFi();                 // Inicializar WiFi

    // Esperar a que se establezca la conexión WiFi
    Serial.println("Esperando conexión WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConectado a WiFi.");
}

void loop() {
    maintainBLE();              // Mantener la comunicación BLE
    // Lógica adicional del bucle principal, si es necesario
    // Por ejemplo, leer el estado del botón y ajustar el volumen
    if (digitalRead(buttonVolUpPin) == HIGH) {
        // Aumentar volumen
    }
    if (digitalRead(buttonVolDownPin) == HIGH) {
        // Disminuir volumen
    }
    // Leer el nivel de batería y actualizar BLE
    float batteryLevel = readBatteryLevel();  // Función que debes implementar para leer el nivel de batería
    updateBatteryLevel(batteryLevel);          // Actualizar nivel de batería en BLE
    delay(1000);  // Esperar un segundo antes de la siguiente iteración
}

