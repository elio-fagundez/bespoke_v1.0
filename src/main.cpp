// main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "pins.h"
#include "modules/ble.h"
#include "modules/mqtt.h"
#include "modules/wifi.h"
#include "modules/adc_battery.h"
#include "modules/sd_card.h"
#include "modules/spk.h"
#include "modules/mic.h"

const int ledPowerOnPin = GPIO_POWER_ON;
int32_t audioBuffer[256];

void setup() {
    pinMode(ledPowerOnPin, OUTPUT);
    digitalWrite(ledPowerOnPin, HIGH);

    Serial.begin(BAUD_RATE);
    delay(1000);

    
    initBatteryMeasurement();
    delay(10);
    initMQTT();
    delay(10);
    initWiFi();
    delay(10);
    initMicrophone();
    delay(500);
    //initBLE(); // inicializar BLE unicamente cuando se utilice
    delay(10);

    // Inicializar el speaker
    Serial.println("Inicializando el speaker...");
    initSpeaker(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Speaker inicializado.");
    delay(500);
    // Inicializar la tarjeta SD
    if (!initSDCard()) {
        Serial.println("Error al inicializar la tarjeta SD.");
    } else {
        Serial.println("Tarjeta SD inicializada correctamente.");
        writeFile(SD, "/log.txt", "AI Teddy Bear started.\n");
    }
    delay(500);
}

void loop() {
   // maintainBLE();
    maintainSpeaker(); // Mantener activo el speaker

    // Leer el micrófono
    //readMicrophone(audioBuffer, 256);
    /*for (int i = 0; i < 256; i++) {
        int32_t scaledValue = audioBuffer[i] / 1000000;
        Serial.print(scaledValue);
        Serial.print(" ");
    }*/

    delay(1);
}
