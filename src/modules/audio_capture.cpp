#include "audio_capture.h"
#include "config.h"
#include "wifi.h"
#include <HTTPClient.h>

// Parámetros de audio
#define AUDIO_SAMPLE_RATE       SAMPLE_RATE
#define AUDIO_BITS_PER_SAMPLE   SAMPLE_BITS
#define AUDIO_CHANNELS          2       // Estéreo

// Buffer para almacenar los datos de audio
static uint8_t* audioBuffer = nullptr;
static size_t audioBufferSize = 0;
static size_t audioDataIndex = 0;

// Variables para controlar la captura de audio
static bool capturingAudio = false;
static unsigned long captureStartTime = 0;

// Estructura del encabezado WAV
struct WAV_HEADER {
    char riff[4] = {'R','I','F','F'};
    uint32_t flength = 0; // Se actualizará al finalizar la grabación
    char wave[4] = {'W','A','V','E'};
    char fmt[4] = {'f','m','t',' '};
    uint32_t chunk_size = 16;
    uint16_t format_tag = 1;
    uint16_t num_chans = AUDIO_CHANNELS; // Estéreo
    uint32_t srate = AUDIO_SAMPLE_RATE;
    uint32_t bytes_per_sec = AUDIO_SAMPLE_RATE * AUDIO_CHANNELS * (AUDIO_BITS_PER_SAMPLE / 8);
    uint16_t bytes_per_samp = AUDIO_CHANNELS * (AUDIO_BITS_PER_SAMPLE / 8);
    uint16_t bits_per_samp = AUDIO_BITS_PER_SAMPLE;
    char dat[4] = {'d','a','t','a'};
    uint32_t dlength = 0; // Se actualizará al finalizar la grabación
} wavHeader;

void initAudioCapture() {
    // No es necesario inicializar nada aquí por ahora
}

void startAudioCapture() {
    if (capturingAudio) {
        Serial.println("La captura de audio ya está en progreso.");
        return;
    }

    // Calcular el tamaño del buffer para 10 segundos de audio
    audioBufferSize = AUDIO_SAMPLE_RATE * AUDIO_CHANNELS * (AUDIO_BITS_PER_SAMPLE / 8) * 10; // 10 segundos
    audioBuffer = (uint8_t*)malloc(audioBufferSize);
    if (!audioBuffer) {
        Serial.println("Error: No se pudo asignar memoria para el buffer de audio.");
        return;
    }

    // Inicializar índice del buffer
    audioDataIndex = 0;

    // Reiniciar las longitudes en el encabezado WAV
    wavHeader.flength = 0;
    wavHeader.dlength = 0;

    // Comenzar la captura
    capturingAudio = true;
    captureStartTime = millis();

    Serial.println("Captura de audio iniciada.");
}

void processAudioCapture(int16_t* audioData, size_t dataSize) {
    if (!capturingAudio) {
        return;
    }

    size_t bytesToCopy = dataSize * sizeof(int16_t);

    // Verificar si hay espacio suficiente en el buffer
    if ((audioDataIndex + bytesToCopy) > audioBufferSize) {
        // Ajustar bytes a copiar para evitar desbordamiento
        bytesToCopy = audioBufferSize - audioDataIndex;
        capturingAudio = false; // Detener captura
        Serial.println("Buffer de audio lleno. Deteniendo captura.");
    }

    // Copiar datos al buffer de audio
    memcpy(audioBuffer + audioDataIndex, audioData, bytesToCopy);
    audioDataIndex += bytesToCopy;

    // Verificar si se alcanzó el límite de tiempo
    if ((millis() - captureStartTime) >= 10000) { // 10 segundos
        capturingAudio = false;
        Serial.println("Tiempo máximo de captura alcanzado.");
    }

    if (!capturingAudio) {
        // Finalizar la captura
        finalizeAudioCapture();
    }
}

void finalizeAudioCapture() {
    // Actualizar longitudes en el encabezado WAV
    wavHeader.dlength = audioDataIndex;
    wavHeader.flength = audioDataIndex + sizeof(WAV_HEADER) - 8;

    // Prepend el encabezado WAV a los datos de audio
    uint8_t* wavData = (uint8_t*)malloc(audioDataIndex + sizeof(WAV_HEADER));
    if (!wavData) {
        Serial.println("Error: No se pudo asignar memoria para los datos WAV.");
        free(audioBuffer);
        return;
    }
    memcpy(wavData, &wavHeader, sizeof(WAV_HEADER));
    memcpy(wavData + sizeof(WAV_HEADER), audioBuffer, audioDataIndex);

    // Enviar los datos de audio al servidor
    sendAudioToServer(wavData, audioDataIndex + sizeof(WAV_HEADER));

    // Liberar memoria
    free(audioBuffer);
    audioBuffer = nullptr;
    free(wavData);

    Serial.println("Captura de audio completada y enviada al servidor.");
}

void sendAudioToServer(uint8_t* data, size_t length) {
    if (!isWiFiConnected()) {
        Serial.println("No conectado a WiFi. No se puede enviar el audio.");
        return;
    }

    HTTPClient http;
    String serverUrl = "http://your_server_address/receive_audio"; // Reemplaza con la URL de tu servidor

    http.begin(serverUrl);
    http.addHeader("Content-Type", "audio/wav");

    int httpResponseCode = http.POST(data, length);

    if (httpResponseCode > 0) {
        Serial.print("Audio enviado. Código de respuesta: ");
        Serial.println(httpResponseCode);
        String response = http.getString();
        Serial.println("Respuesta del servidor: ");
        Serial.println(response);
    } else {
        Serial.print("Error al enviar el audio. Código de respuesta: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

bool isAudioCapturing() {
    return capturingAudio;
}

bool isAudioCaptureComplete() {
    return !capturingAudio && audioDataIndex > 0;
}

