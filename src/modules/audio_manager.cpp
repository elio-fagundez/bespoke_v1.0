#include "audio_manager.h"
#include <driver/i2s.h>

void initAudioManager() {
    // Configurar I2S
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = (i2s_bits_per_sample_t)SAMPLE_BITS,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, // Estéreo
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = BUFFER_SIZE,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_PIN_CLK,
        .ws_io_num = I2S_PIN_WS,
        .data_out_num = I2S_PIN_DATA, // No se usa en modo RX
        .data_in_num = I2S_PIN_DATA
    };

    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);
    i2s_zero_dma_buffer(I2S_NUM);

    Serial.println("I2S inicializado por AudioManager.");
}

size_t readAudioData(int16_t* buffer, size_t samples) {
    size_t bytesRead = 0;
    size_t bytesToRead = samples * sizeof(int16_t);

    esp_err_t result = i2s_read(I2S_NUM, buffer, bytesToRead, &bytesRead, portMAX_DELAY);
    if (result != ESP_OK) {
        Serial.println("Error al leer datos de audio desde I2S.");
    }
    return bytesRead / sizeof(int16_t); // Devolver el número de muestras leídas
}
