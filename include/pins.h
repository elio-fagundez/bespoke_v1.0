#ifndef PINS_H
#define PINS_H

// Definiciones de pines
#define GPIO_POWER_ON 35          // Pin para LED de encendido
// #define GPIO_BATTERY_ADC 7        // Pin GPIO7 para lectura del nivel de batería
#define GPIO_BATTERY_ADC GPIO_NUM_7 // Definición del pin para la lectura de la batería (GPIO7)

// Pines para la interfaz SPI de la tarjeta SD
#define SD_CS_PIN 19    // Pin CS de la tarjeta SD
#define SD_SCK_PIN 18   // Pin SCK (Serial Clock)
#define SD_MISO_PIN 17  // Pin MISO (Master In Slave Out)
#define SD_MOSI_PIN 16  // Pin MOSI (Master Out Slave In)

// Pines para el control de volumen
#define GPIO_BTN_VOL_UP 37 // Incrementar volumen
#define GGPIO_BTN_VOL_DOWN  36 // decrementar volumen

// Pines para el microphone
#define GPIO_MIC_BCK     42
#define GPIO_MIC_WS      40
#define GPIO_MIC_DATA_IN 41


// Define I2S Speaker connections
#define I2S_DOUT  10
#define I2S_BCLK  11
#define I2S_LRC   12
#define I2S_SD   46

// Define volume control pins
#define INC_VOL 37
#define DEC_VOL 36


#endif // PINS_H
