// adc_battery.h
#ifndef ADC_BATTERY_H
#define ADC_BATTERY_H

#include <Arduino.h>

// Inicializa la medición de batería
void initBatteryMeasurement();

// Lee el nivel de la batería
float readBatteryLevel();

#endif // ADC_BATTERY_H

