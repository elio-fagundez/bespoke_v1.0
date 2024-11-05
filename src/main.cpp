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

// Variables globales

void setup() {
  // Inicializar comunicación serial a 115200 baudios
  Serial.begin(9600);

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

    // Aquí puedes agregar el código para enviar el nivel de batería a la app o servidor remoto

    delay(5000); // Esperar 5 segundos antes de la próxima lectura
  } else {
    // Manejar solicitudes de clientes en modo AP
    handleClientRequests();
  }
}



