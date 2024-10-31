//Adc Battery.cpp
#include "adc_battery.h"
#include "pins.h"  
#include <Arduino.h> 
#include "adc_battery.h"
#include "pins.h"
#include <Arduino.h>

const int analogPin = GPIO_BATTERY_ADC; 

void initBatteryMeasurement() {
    pinMode(analogPin, INPUT);
} // here finish inizialitazion process

float readBatteryLevelPercentage() {
    int analogValue = analogRead(analogPin);
    float voltage = analogValue * (3.3 / 4095.0);
    float batteryPercentage = (voltage / 3.3) * 100.0;
    if (batteryPercentage > 100.0) batteryPercentage = 100.0;
    if (batteryPercentage < 0.0) batteryPercentage = 0.0;
    return batteryPercentage;
} // here finish batery reading process

