// sd_card.h
#pragma once
#include "FS.h"
#include "SD.h"

// Inicialización de la tarjeta SD
bool initSDCard();

// Escritura de datos en un archivo en la tarjeta SD
void writeFile(fs::FS &fs, const char *path, const char *message);
