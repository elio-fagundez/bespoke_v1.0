#ifndef TRIGGER_DET_H
#define TRIGGER_DET_H

#include <Arduino.h>

// Inicializa el módulo de detección de palabras clave
void initTriggerDetection();

// Verifica si se ha detectado la palabra clave
bool isTriggerDetected();

// Procesa los datos de audio para detectar el trigger
void processAudioForTrigger(int16_t* audioData, size_t dataSize);

#endif // TRIGGER_DET_H
