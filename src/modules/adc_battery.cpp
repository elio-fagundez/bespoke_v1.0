#include "adc_battery.h"

// Variables para la medición de batería
const uint16_t ADC_MAX_VALUE = 4095;       // Resolución del ADC de 12 bits
const float REFERENCE_VOLTAGE = 3.3;       // Voltaje de referencia del ADC
const float BATTERY_MAX_VOLTAGE = 4.2;     // Voltaje máximo de la batería (ajustar según especificación)
const float BATTERY_MIN_VOLTAGE = 3.0;     // Voltaje mínimo de la batería (ajustar según especificación)

// Factor de división si se usa un divisor de voltaje (ajustar según el hardware)
const float VOLTAGE_DIVIDER_RATIO = 2.0;   // Ejemplo: si se usa un divisor 1:2

void initBatteryADC() {
  // Configurar el pin GPIO_BATTERY_ADC como entrada analógica
  pinMode(GPIO_BATTERY_ADC, INPUT);

  // Configurar la resolución del ADC
  analogReadResolution(12); // Resolución de 12 bits (0-4095)

  // Mensaje de inicialización
  Serial.println("ADC de batería inicializado.");
}

uint8_t readBatteryLevel() {
  // Leer el valor del ADC
  uint16_t adcValue = analogRead(GPIO_BATTERY_ADC);

  // Convertir el valor ADC a voltaje real de la batería
  float voltage = ((float)adcValue / ADC_MAX_VALUE) * REFERENCE_VOLTAGE * VOLTAGE_DIVIDER_RATIO;

  // Mapear el voltaje al porcentaje de batería
  float percentage = ((voltage - BATTERY_MIN_VOLTAGE) / (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE)) * 100.0;

  // Limitar el porcentaje entre 0 y 100
  if (percentage > 100.0) percentage = 100.0;
  if (percentage < 0.0) percentage = 0.0;

  // Mensaje de depuración
  Serial.print("Voltaje de batería: ");
  Serial.print(voltage, 2);
  Serial.print(" V, Nivel de batería: ");
  Serial.print(percentage, 1);
  Serial.println("%");

  return (uint8_t)percentage;
}


