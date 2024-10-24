// adc_battery.cpp
#include "adc_battery.h"
#include <driver/adc.h>
#include <esp_adc_cal.h>

#define BATTERY_CHANNEL ADC1_CHANNEL_0 // Cambia esto según el canal ADC que estés usando

void initBatteryMeasurement() {
    // Configuración del ADC
    adc1_config_width(ADC_WIDTH_BIT_12); // Resolución de 12 bits
    adc1_config_channel_atten(BATTERY_CHANNEL, ADC_ATTEN_DB_0); // Atenuación de 0 dB
}

float readBatteryLevel() {
    // Leer el voltaje del ADC
    int rawValue = adc1_get_raw(BATTERY_CHANNEL);
    float voltage = (rawValue / 4095.0) * 3.3; // Convierte a voltaje (ajusta 3.3V según tu referencia)

    // Puedes agregar lógica para convertir a nivel de batería en porcentaje si es necesario
    return voltage; // Retornar el voltaje leído
}
