#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#include <Arduino.h>

// Inicializa el módulo de captura de audio (si es necesario)
void initAudioCapture();

// Inicia la captura de audio
void startAudioCapture();

// Procesa los datos de audio para almacenar la captura
void processAudioCapture(int16_t* audioData, size_t dataSize);

// Verifica si la captura de audio está en progreso
bool isAudioCapturing();

// Verifica si la captura de audio ha finalizado
bool isAudioCaptureComplete();

#endif // AUDIO_CAPTURE_H
