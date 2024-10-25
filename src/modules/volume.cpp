// volume.cpp
#include "volume.h"
#include "pins.h"
#include "config.h"
#include <Preferences.h>  // Para guardar el valor de volumen en la memoria no volátil

// Inicializar el objeto Preferences para el almacenamiento
Preferences preferences;

// Definir el rango de volumen
#define MAX_VOLUME 100
#define MIN_VOLUME 0

// Definir los pines de los botones
const int buttonIncreasePin = GPIO_BTN_VOL_UP; // GPIO37 - definido en pins.h
const int buttonDecreasePin = GPIO_BTN_VOL_DOWN; // GPIO36 - definido en pins.h

// Variable para almacenar el nivel de volumen
int volumeLevel = 50; // Valor inicial del volumen

void initVolumeControl() {
    pinMode(buttonIncreasePin, INPUT_PULLUP); // Configurar el pin de incremento como entrada con resistencia de pull-up
    pinMode(buttonDecreasePin, INPUT_PULLUP); // Configurar el pin de decremento como entrada con resistencia de pull-up

    preferences.begin("volume", false); // Iniciar la NVS (almacenamiento no volátil)
    loadVolume(); // Cargar el último valor de volumen almacenado
}

void increaseVolume() {
    if (digitalRead(buttonIncreasePin) == LOW) {
        volumeLevel = min(volumeLevel + 1, MAX_VOLUME); // Aumentar el volumen con límite en MAX_VOLUME
        saveVolume(); // Guardar el nuevo valor de volumen
    }
}

void decreaseVolume() {
    if (digitalRead(buttonDecreasePin) == LOW) {
        volumeLevel = max(volumeLevel - 1, MIN_VOLUME); // Disminuir el volumen con límite en MIN_VOLUME
        saveVolume(); // Guardar el nuevo valor de volumen
    }
}

void saveVolume() {
    preferences.putInt("level", volumeLevel); // Guardar el valor de volumen en NVS
}

void loadVolume() {
    volumeLevel = preferences.getInt("level", 50); // Cargar el valor almacenado o 50 si no hay valor previo
}

int getVolumeLevel() {
    return volumeLevel;
}
