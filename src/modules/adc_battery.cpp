#include "adc_battery.h"
#include "pins.h"  // Asegúrate de incluir pins.h para acceder a la definición de GPIO_BATTERY_ADC
#include <driver/adc.h>
#include <esp_adc_cal.h>

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


