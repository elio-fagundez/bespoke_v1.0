// spk.cpp
#include "spk.h"
#include "Audio.h"
#include "WiFi.h"

// Crear objeto de audio de ámbito global
static Audio audio;

void initSpeaker(const char* streamURL) {
    // Configurar el amplificador MAX98357 con los pines I2S definidos en pins.h
    audio.setPinout(GPIO_SPK_BCLK, GPIO_SPK_LRC, GPIO_SPK_DOUT);
    audio.setVolume(10); // Configurar un volumen predeterminado

    // Conectar al stream de audio
    audio.connecttohost(streamURL);
}

void loopSpeaker() {
    // Mantener la reproducción de audio
    audio.loop();
}