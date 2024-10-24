#include "adc_battery.h"
#include "pins.h"  // Asegúrate de incluir pins.h para acceder a la definición de GPIO_BATTERY_ADC
#include <Arduino.h> // Incluye la biblioteca de Arduino

// Definir el pin GPIO donde se conectará la señal analógica
// adc_battery.cpp
#include "adc_battery.h"
#include "pins.h"
#include <Arduino.h>

const int analogPin = GPIO_BATTERY_ADC; // Define el pin de acuerdo a lo que hayas configurado en pins.h

void initBatteryMeasurement() {
    pinMode(analogPin, INPUT);
}

float readBatteryLevelPercentage() {
    int analogValue = analogRead(analogPin);
    float voltage = analogValue * (3.3 / 4095.0);
    float batteryPercentage = (voltage / 3.3) * 100.0;
    if (batteryPercentage > 100.0) batteryPercentage = 100.0;
    if (batteryPercentage < 0.0) batteryPercentage = 0.0;
    return batteryPercentage;
}

