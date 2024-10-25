// sd_card.cpp
#include "sd_card.h"
#include "pins.h"
#include <SPI.h>
#include <Arduino.h> // Para usar funciones como Serial

bool initSDCard() {
    // Inicializar la interfaz SPI con pines personalizados
    SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

    // Inicializar la tarjeta SD
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Fallo al montar la tarjeta SD.");
        return false;
    }
    Serial.println("Tarjeta SD montada correctamente.");
    return true;
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
    Serial.printf("Abriendo archivo %s para escribir...\n", path);

    File file = fs.open(path, FILE_APPEND);  // Abrir el archivo en modo de añadir (APPEND)
    if (!file) {
        Serial.println("Fallo al abrir el archivo para escribir.");
        return;
    }
    if (file.print(message)) {
        Serial.println("Datos escritos correctamente.");
    } else {
        Serial.println("Error al escribir los datos.");
    }
    file.close();
}
