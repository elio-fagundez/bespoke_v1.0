#ifndef ADC_BATTERY_H
#define ADC_BATTERY_H

// Incluir las bibliotecas necesarias
#include <driver/adc.h>

// Prototipos de funciones
void initBatteryMeasurement();
float readBatteryLevel();

// Definición del canal ADC para GPIO7
#define BATTERY_CHANNEL ADC1_CHANNEL_0 // Cambiar este valor si es necesario

#endif // ADC_BATTERY_H


