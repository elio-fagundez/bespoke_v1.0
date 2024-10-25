// mic.cpp
#include "mic.h"
#include <driver/i2s.h>
#include "pins.h" // Para definir los pines relacionados con el micrófono

// Configuración del I2S y los pines asociados
static const i2s_port_t i2s_num = I2S_NUM_1;
static const size_t bufferLength = 256;

static const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 30072,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
};

static const i2s_pin_config_t pin_config = {
    .bck_io_num = GPIO_MIC_BCK, // Pines definidos en "pins.h"
    .ws_io_num = GPIO_MIC_WS,   
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = GPIO_MIC_DATA_IN 
};

void initMicrophone() {
    // Instalar el controlador I2S
    i2s_driver_install(i2s_num, &i2s_config, 0, NULL);
    
    // Ajustes específicos de sincronización para I2S
    REG_SET_BIT(I2S_RX_TIMING_REG(i2s_num), BIT(9));
    REG_SET_BIT(I2S_TX_CONF_REG(i2s_num), I2S_RX_MSB_SHIFT);
    
    // Configurar los pines de I2S
    i2s_set_pin(i2s_num, &pin_config);
}

void readMicrophone(int32_t *buffer, size_t len) {
    size_t bytesRead;
    i2s_read(i2s_num, buffer, len * sizeof(int32_t), &bytesRead, portMAX_DELAY);
}
