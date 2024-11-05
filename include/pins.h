#ifndef PINS_H
#define PINS_H

// Led Power ON
#define GPIO_POWER_ON 35 

// ADC input to battery
#define GPIO_BATTERY_ADC GPIO_NUM_7 

// SPI Interfaz
#define SD_CS_PIN 19    
#define SD_SCK_PIN 18   
#define SD_MISO_PIN 17  
#define SD_MOSI_PIN 16 

// Volume Control 
#define INC_VOL 37
#define DEC_VOL 36

// Configuración del I2S 
#define I2S_NUM           I2S_NUM_1
#define SAMPLE_RATE       16000
#define SAMPLE_BITS       32
#define BUFFER_SIZE       128
#define I2S_PIN_WS        40
#define I2S_PIN_CLK       42
#define I2S_PIN_DATA      41

// I2S Speaker (I2S_NUM_1)
#define I2S_DOUT  10
#define I2S_BCLK  11
#define I2S_LRC   12
#define I2S_SD    46


#endif // PINS_H
