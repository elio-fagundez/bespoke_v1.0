// ble.h
#ifndef BLE_H
#define BLE_H

#include <Arduino.h>

// Inicializar el módulo BLE
void initBLE();

// Mantener la comunicación BLE
void maintainBLE();

// Actualizar el nivel de batería en la característica BLE correspondiente
void updateBatteryLevel(float level);

#endif // BLE_H

