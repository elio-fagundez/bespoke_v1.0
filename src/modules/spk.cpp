// spk.cpp
#include "spk.h"
#include "WiFi.h"
#include "Audio.h"
#include "pins.h"

// Crear objeto de audio de forma global
Audio audio;
int volume = 10;
unsigned long lastChange = 0;
const unsigned long volumeChangeDelay = 500;
const int volumeStep = 2;

void initSpeaker(const char* ssid, const char* password) {
    pinMode(I2S_SD, OUTPUT);
    digitalWrite(I2S_SD, HIGH);

    // Configurar los pines de control de volumen como entradas con resistencias pull-up
    pinMode(INC_VOL, INPUT_PULLUP);
    pinMode(DEC_VOL, INPUT_PULLUP);

    // Configurar el WiFi
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // WiFi conectado, imprimir IP
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("");

    // Configurar los pines del amplificador I2S
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

    // Configurar el volumen inicial
    audio.setVolume(volume);

    // Conectar a la estación de radio
    audio.connecttohost("0n-80s.radionetz.de:8000/0n-70s.mp3");
    delay(500);
}

void maintainSpeaker() {
    // Comprobar los botones de volumen solo si ha pasado suficiente tiempo
    if (millis() - lastChange > volumeChangeDelay) {
        if (digitalRead(INC_VOL) == LOW) {
            if (volume + volumeStep <= 100) {
                volume += volumeStep;
                audio.setVolume(volume);
                Serial.print("Volume increased to: ");
                Serial.println(volume);
                lastChange = millis();
                delay(100);
            }
        }

        if (digitalRead(DEC_VOL) == LOW) {
            if (volume - volumeStep >= 0) {
                volume -= volumeStep;
                audio.setVolume(volume);
                Serial.print("Volume decreased to: ");
                Serial.println(volume);
                lastChange = millis();
                delay(100);
            }
        }
    }

    // Ejecutar el bucle del reproductor de audio
    audio.loop();
}

// Audio status functions
void audio_info(const char *info) {
  Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info) { // id3 metadata
  Serial.print("id3data     "); Serial.println(info);
}
void audio_eof_mp3(const char *info) { // end of file
  Serial.print("eof_mp3     "); Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     "); Serial.println(info);
}
void audio_showstreaminfo(const char *info) {
  Serial.print("streaminfo  "); Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle "); Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     "); Serial.println(info);
}
void audio_commercial(const char *info) { // duration in sec
  Serial.print("commercial  "); Serial.println(info);
}
void audio_icyurl(const char *info) { // homepage
  Serial.print("icyurl      "); Serial.println(info);
}
void audio_lasthost(const char *info) { // stream URL played
  Serial.print("lasthost    "); Serial.println(info);
}
void audio_eof_speech(const char *info) {
  Serial.print("eof_speech  "); Serial.println(info);
}
