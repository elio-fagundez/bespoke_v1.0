#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

// Inicializa el módulo del altavoz
void initSpeaker();

// Reproduce un archivo de audio desde un buffer
void playAudio(uint8_t* data, size_t length);

// Función para procesar el audio recibido del servidor
void processServerAudio();

// Funciones para controlar el volumen
void increaseVolume();
void decreaseVolume();

// Obtener el nivel de volumen actual
uint8_t getVolumeLevel();

#endif // SPEAKER_H
