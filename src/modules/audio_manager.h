#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <Arduino.h>
#include "pins.h"

// Inicializa el I2S para captura de audio
void initAudioManager();

// Lee datos de audio desde el I2S
// Devuelve el número de bytes leídos
size_t readAudioData(int16_t* buffer, size_t samples);

#endif // AUDIO_MANAGER_H
