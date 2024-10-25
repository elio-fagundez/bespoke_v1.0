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
#include "modules/volume.h"
#include "modules/mic.h"
#include "modules/spk.h" 

const int ledPowerOnPin = GPIO_POWER_ON;
int32_t audioBuffer[256];

// Configuración del stream para el speaker
const char* streamURL = "http://vis.media-ice.musicradio.com/CapitalMP3";

void setup() {
    pinMode(ledPowerOnPin, OUTPUT);
    digitalWrite(ledPowerOnPin, HIGH);

    Serial.begin(BAUD_RATE);
    delay(1000);

    initBLE();
    initBatteryMeasurement();
    initMQTT();
    initWiFi();
    initMicrophone();

    // Inicializar el speaker con la URL del stream
    initSpeaker(streamURL);

    // Inicializar la tarjeta SD
    if (!initSDCard()) {
        Serial.println("Error al inicializar la tarjeta SD.");
    } else {
        Serial.println("Tarjeta SD inicializada correctamente.");
        // Guardar un mensaje de inicio en la tarjeta SD
        writeFile(SD, "/log.txt", "AI Teddy Bear started.\n");
    }

    // Esperar conexión WiFi en la función de WiFi externa
    waitForWiFiConnection();

    // Inicializar control de volumen
    initVolumeControl();
}

void loop() {
    maintainBLE();

    // Control de volumen con botones
    increaseVolume();
    decreaseVolume();

    // Leer el micrófono
    readMicrophone(audioBuffer, 256);
    for (int i = 0; i < 256; i++) {
        int32_t scaledValue = audioBuffer[i] / 1000000;
        Serial.print(scaledValue);
        Serial.print(" ");
    }
    Serial.println();

    // Mantener reproducción del speaker
    loopSpeaker();

    delay(1000);
}
