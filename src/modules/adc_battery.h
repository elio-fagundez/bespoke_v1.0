#ifndef ADC_BATTERY_H
#define ADC_BATTERY_H

#include <Arduino.h>
#include "pins.h"

// Inicializa el ADC para la medición de la batería
void initBatteryADC();

// Lee el nivel de la batería y devuelve un porcentaje de 0 a 100%
uint8_t readBatteryLevel();

#endif // ADC_BATTERY_H




