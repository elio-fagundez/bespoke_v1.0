// ble.cpp
#include "ble.h"
#include "config.h"
#include "adc_battery.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UUIDs para el servicio y la característica del nivel de batería
#define SERVICE_UUID        "180F" // Servicio estándar de batería
#define CHARACTERISTIC_UUID "2A19" // Característica estándar de nivel de batería

// Instancias globales para el servidor y la característica BLE
BLEServer* pServer = nullptr;
BLECharacteristic* pBatteryCharacteristic = nullptr;

void initBLE() {
    // Inicializar el dispositivo BLE
    BLEDevice::init("AI_Teddy_Bear");
    pServer = BLEDevice::createServer();

    // Crear un servicio de batería
    BLEService* pBatteryService = pServer->createService(SERVICE_UUID);

    // Crear una característica para el nivel de batería
    pBatteryCharacteristic = pBatteryService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );

    // Añadir descriptor para habilitar notificaciones
    pBatteryCharacteristic->addDescriptor(new BLE2902());

    // Iniciar el servicio y comenzar a anunciar
    pBatteryService->start();
    BLEDevice::startAdvertising();
    Serial.println("BLE initialized and advertising started.");
}

// Mantener la comunicación BLE
void maintainBLE() {
    // Aquí puedes agregar lógica adicional si es necesario, como controlar la conexión o manejar eventos.
}

// Actualizar el nivel de batería
void updateBatteryLevel(float level) {
    uint8_t batteryLevel = static_cast<uint8_t>(level);
    pBatteryCharacteristic->setValue(&batteryLevel, 1);
    pBatteryCharacteristic->notify();
    Serial.printf("Battery level updated: %d%%\n", batteryLevel);
}
