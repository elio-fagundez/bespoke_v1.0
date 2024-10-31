// sd_card.cpp
#include "sd_card.h"
#include "pins.h"
#include <SPI.h>
#include <Arduino.h> 

bool initSDCard() {

    SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Failed to mount SD Card.");
        return false;
    }
    Serial.println("SD Card mounting successfully.");
    return true;
} // here finish initialization processs
void writeFile(fs::FS &fs, const char *path, const char *message) {
    Serial.printf("Opening File %s to write...\n", path);

    File file = fs.open(path, FILE_APPEND);  
    if (!file) {
        Serial.println("Failed opening file to write.");
        return;
    }
    if (file.print(message)) {
        Serial.println("Dat writed successfully.");
    } else {
        Serial.println("Wrong writing data.");
    }
    file.close();
} // here finish writing processs