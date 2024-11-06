#include "modules/speaker.h"
#include "pins.h"
#include "config.h"
#include "wifi.h"
#include <driver/i2s.h>
#include <HTTPClient.h>

// Parámetros de audio
#define SPEAKER_SAMPLE_RATE       16000    // Tasa de muestreo
#define SPEAKER_BITS_PER_SAMPLE   I2S_BITS_PER_SAMPLE_16BIT

// Variable para controlar el volumen (rango 0 - 100)
static uint8_t volumeLevel = 50; // Nivel de volumen inicial al 50%
static float volumeGain = 0.5f;  // Ganancia de volumen inicial

void updateVolumeGain() {
    volumeGain = volumeLevel / 100.0f;
}

void initSpeaker() {
    // Configurar I2S para el altavoz
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SPEAKER_SAMPLE_RATE,
        .bits_per_sample = SPEAKER_BITS_PER_SAMPLE,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, // Estéreo
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK,
        .ws_io_num = I2S_LRC,
        .data_out_num = I2S_DOUT,
        .data_in_num = I2S_PIN_NO_CHANGE // No se usa en modo TX
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    i2s_zero_dma_buffer(I2S_NUM_0);

    // Inicializar volumen
    volumeLevel = 50;
    updateVolumeGain();

    Serial.println("I2S inicializado para el altavoz.");
}

void playAudio(uint8_t* data, size_t length) {
    size_t bytes_written = 0;
    size_t total_bytes_written = 0;

    // Dado que estamos tratando con muestras de 16 bits, procesamos los datos como int16_t
    int16_t* samples = (int16_t*)data;
    size_t num_samples = length / sizeof(int16_t);

    // Crear un buffer para almacenar las muestras ajustadas
    int16_t* adjusted_samples = (int16_t*)malloc(length);
    if (!adjusted_samples) {
        Serial.println("Error: No se pudo asignar memoria para ajustar el volumen.");
        return;
    }

    // Ajustar las muestras según el volumen
    for (size_t i = 0; i < num_samples; i++) {
        float sample = (float)samples[i];
        sample *= volumeGain;
        // Limitar el valor para evitar desbordamientos
        if (sample > 32767.0f) sample = 32767.0f;
        if (sample < -32768.0f) sample = -32768.0f;
        adjusted_samples[i] = (int16_t)sample;
    }

    uint8_t* adjusted_data = (uint8_t*)adjusted_samples;

    // Enviar los datos al I2S
    while (total_bytes_written < length) {
        size_t bytes_to_write = length - total_bytes_written;
        if (bytes_to_write > 512) {
            bytes_to_write = 512;
        }

        i2s_write(I2S_NUM_0, adjusted_data + total_bytes_written, bytes_to_write, &bytes_written, portMAX_DELAY);
        total_bytes_written += bytes_written;
    }

    free(adjusted_samples);
}

void processServerAudio() {
    if (!isWiFiConnected()) {
        Serial.println("No conectado a WiFi. No se puede recibir el audio.");
        return;
    }

    HTTPClient http;
    String serverUrl = "http://your_server_address/get_audio"; // Reemplaza con la URL de tu servidor

    http.begin(serverUrl);

    int httpResponseCode = http.GET();

    if (httpResponseCode == HTTP_CODE_OK) {
        // Obtener el tamaño del contenido
        int len = http.getSize();

        // Crear un buffer para almacenar los datos recibidos
        uint8_t* buffer = (uint8_t*)malloc(len);
        if (!buffer) {
            Serial.println("Error: No se pudo asignar memoria para el audio.");
            http.end();
            return;
        }

        WiFiClient* stream = http.getStreamPtr();
        int total_bytes_read = 0;
        while (http.connected() && total_bytes_read < len) {
            size_t size_available = stream->available();
            if (size_available) {
                int bytes_read = stream->readBytes(buffer + total_bytes_read, size_available);
                total_bytes_read += bytes_read;
            }
            delay(1);
        }

        Serial.println("Audio recibido del servidor. Iniciando reproducción...");
        playAudio(buffer, len);
        Serial.println("Reproducción finalizada.");

        free(buffer);
    } else {
        Serial.print("Error al recibir el audio. Código de respuesta: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void increaseVolume() {
    if (volumeLevel < 100) {
        volumeLevel += 10;
        updateVolumeGain();
        Serial.print("Volumen incrementado a: ");
        Serial.println(volumeLevel);
    }
}

void decreaseVolume() {
    if (volumeLevel > 0) {
        volumeLevel -= 10;
        updateVolumeGain();
        Serial.print("Volumen decrementado a: ");
        Serial.println(volumeLevel);
    }
}

uint8_t getVolumeLevel() {
    return volumeLevel;
}
