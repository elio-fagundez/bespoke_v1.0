//////////////////////////////////////************************Bespoke V1.0 A*********************////////////////////////////////////
/*
 This firmware it is responsible for running the functions of the AI ​​teddy bear project, 
 which will be used for language learning through openAI, aimed at children.

 Hardware Main Components:
 * ESP32-S3
 * DIGITAL MENS MIC (SH)
 * SPEAKER 4R 5W
 * BATTERY ION LITHIUM 3.7V - 4000mA
 
 Software: 
 * App Phoenyx in python
 
 Necessary API'S:
 * Speech to text (Google TTS / Amazon transcriber)
 * OpenAI API 
 * text to speech (Google STT / Amazon Poly)
 

 Created xx November 2024
 by Elio Fagundez
 */

// Main libraries and modules 
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <SD_MMC.h>
#include <SPIFFS.h>
#include <FFat.h>
#include "pins.h"
#include "modules/esp32_server.h"
#include "modules/sd_card.h"
#include "modules/adc_battery.h"
#include "modules/wifi.h"
#include "modules/audio_manager.h"
#include "modules/audio_capture.h"
#include "modules/trigger_det.h"
#include "modules/speaker.h"

// Variables globales para el manejo de botones
unsigned long lastDebounceTimeInc = 0;
unsigned long lastDebounceTimeDec = 0;
unsigned long debounceDelay = 50; // 50 ms de debounce

int lastButtonStateInc = HIGH;
int lastButtonStateDec = HIGH;

void setup() {
    // Inicializar comunicación serial a 115200 baudios
    Serial.begin(115200);

    // Esperar a que el puerto serie esté listo (opcional)
    while (!Serial) {;}

    // Mensaje de inicio
    Serial.println("Iniciando ESP32...");

    // Configurar GPIO_POWER_ON como salida
    pinMode(GPIO_POWER_ON, OUTPUT);

    // Encender el LED de encendido
    digitalWrite(GPIO_POWER_ON, HIGH);
    Serial.println("LED de encendido activado.");

    // Inicializar ADC de batería
    initBatteryADC();

    // Inicializar tarjeta SD
    initSDCard();

    // Inicializar Audio Manager (I2S para micrófono)
    initAudioManager();

    // Inicializar detección de palabra clave
    initTriggerDetection();

    // Inicializar captura de audio
    initAudioCapture();

    // Inicializar altavoz
    initSpeaker();

    // Configurar botones de volumen
    pinMode(INC_VOL, INPUT_PULLUP);
    pinMode(DEC_VOL, INPUT_PULLUP);

    // Obtener dirección MAC
    String macAddress = getMACAddress();
    Serial.print("Dirección MAC: ");
    Serial.println(macAddress);

    // Inicializar WiFi
    initWiFi();

    // Intentar conectar a WiFi
    if (connectToWiFi()) {
        // Conectado a WiFi, continuar con el programa principal
        Serial.println("Conectado a la red WiFi. Iniciando operaciones normales.");
    } else {
        // No se pudo conectar, iniciar en modo AP para recibir credenciales
        Serial.println("No se pudo conectar a WiFi. Iniciando modo AP.");
        startAPMode();
    }
}

void loop() {
    if (isWiFiConnected()) {
        // Operaciones cuando está conectado a WiFi
        // Leer y enviar nivel de batería

        uint8_t batteryLevel = readBatteryLevel();
        Serial.print("Nivel de batería: ");
        Serial.print(batteryLevel);
        Serial.println("%");

        // Buffer para datos de audio
        const size_t audioBufferSize = BUFFER_SIZE;
        int16_t audioBuffer[audioBufferSize];

        // Leer datos de audio desde AudioManager
        size_t samplesRead = readAudioData(audioBuffer, audioBufferSize);

        if (samplesRead > 0) {
            // Procesar audio para detección de palabra clave
            processAudioForTrigger(audioBuffer, samplesRead);

            // Si se detectó el trigger, iniciar captura de audio
            if (isTriggerDetected() && !isAudioCapturing()) {
                Serial.println("Iniciando captura de audio...");
                startAudioCapture();
            }

            // Procesar captura de audio si está en progreso
            if (isAudioCapturing()) {
                processAudioCapture(audioBuffer, samplesRead);
            }
        }

        // Verificar botones de volumen
        int readingInc = digitalRead(INC_VOL);
        if (readingInc != lastButtonStateInc) {
            lastDebounceTimeInc = millis();
        }
        if ((millis() - lastDebounceTimeInc) > debounceDelay) {
            if (readingInc == LOW) {
                increaseVolume();
                Serial.print("Volumen actual: ");
                Serial.println(getVolumeLevel());
            }
        }
        lastButtonStateInc = readingInc;

        int readingDec = digitalRead(DEC_VOL);
        if (readingDec != lastButtonStateDec) {
            lastDebounceTimeDec = millis();
        }
        if ((millis() - lastDebounceTimeDec) > debounceDelay) {
            if (readingDec == LOW) {
                decreaseVolume();
                Serial.print("Volumen actual: ");
                Serial.println(getVolumeLevel());
            }
        }
        lastButtonStateDec = readingDec;

        delay(10); // Ajustar según sea necesario
    } else {
        // Manejar solicitudes de clientes en modo AP
        handleClientRequests();
    }
}



