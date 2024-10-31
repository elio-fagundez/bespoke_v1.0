//////////////////////////////////////************************Bespoke V1.0 A*********************////////////////////////////////////
// MCU = ESP32-S3 WROON-1

// Main libraries and modules 
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "pins.h"
#include "modules/wifi.h"
#include "modules/adc_battery.h"
#include "modules/sd_card.h"

const int ledPowerOnPin = GPIO_POWER_ON;

// Inizialitation 
void setup() {
    pinMode(ledPowerOnPin, OUTPUT);
    digitalWrite(ledPowerOnPin, HIGH);     //Led indicator to pwr ON

    Serial.begin(BAUD_RATE);
    delay(1000);
    
    initBatteryMeasurement();              //Initialize the battery measurement
    delay(1);
    initWiFi();                            //Initialize WiFi 
    delay(1);  
                                           //Initialize SD Card
    if (!initSDCard()) {
        Serial.println("Error initializing SD card.");
    } else {
        Serial.println("SD card initialized successfully.");
        writeFile(SD, "/log.txt", "AI Teddy Bear started.\n");
    }
    delay(500);
}

void loop() {

}
