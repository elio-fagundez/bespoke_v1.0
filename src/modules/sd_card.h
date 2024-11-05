#ifndef SD_CARD_H
#define SD_CARD_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <SD_MMC.h>
#include "pins.h"

// Inicializa la tarjeta SD
bool initSDCard();

// Verifica si la tarjeta SD está inicializada
bool isSDCardInitialized();

// Lee el contenido de un archivo en la tarjeta SD
String readSDFile(const char* path);

// Escribe datos en un archivo en la tarjeta SD
bool writeSDFile(const char* path, const char* data);

// Crea un directorio en la tarjeta SD
bool createSDDir(const char* path);

// Elimina un archivo o directorio en la tarjeta SD
bool removeSDFile(const char* path);

#endif // SD_CARD_H

