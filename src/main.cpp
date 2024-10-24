// main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "pins.h"
#include "modules/ble.h"
#include "modules/mqtt.h"
#include "modules/wifi.h"
#include "modules/adc_battery.h"

const int ledPowerOnPin = GPIO_POWER_ON;
const int buttonVolUpPin = GPIO_BTN_VOL_UP;
const int buttonVolDownPin = GPIO_BTN_VOL_DOWN;

void setup() {
    pinMode(ledPowerOnPin, OUTPUT);
    digitalWrite(ledPowerOnPin, HIGH);

    Serial.begin(BAUD_RATE);
    delay(1000);

    initBLE();
    initBatteryMeasurement();
    initMQTT();
    initWiFi();

    Serial.println("Esperando conexión WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConectado a WiFi.");
}

void loop() {
    maintainBLE();

    if (digitalRead(buttonVolUpPin) == HIGH) {
        // Aumentar volumen
    }
    if (digitalRead(buttonVolDownPin) == HIGH) {
        // Disminuir volumen
    }

    float batteryLevel = readBatteryLevelPercentage(); // Usa la función correcta
    updateBatteryLevel(batteryLevel); // Asegúrate de que esta función esté definida
    delay(1000);
}
