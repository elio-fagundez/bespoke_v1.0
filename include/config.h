#ifndef CONFIG_H
#define CONFIG_H

// Configuración de WiFi
#define WIFI_CONNECT_TIMEOUT 20000 // Tiempo máximo para conectar a WiFi (en milisegundos)

// Umbrales de batería
#define BATTERY_MAX_VOLTAGE 4.2    // Voltaje máximo de la batería
#define BATTERY_MIN_VOLTAGE 3.0    // Voltaje mínimo de la batería

// Relación del divisor de voltaje (ajustar según el hardware)
#define VOLTAGE_DIVIDER_RATIO 2.0  // Ejemplo: si se usa un divisor 1:2

// Umbral para detección de palabra clave
#define TRIGGER_THRESHOLD 0.7      // Ajustar según la precisión del modelo

// Configuración de audio
#define SAMPLE_RATE       16000    // Tasa de muestreo de audio
#define SAMPLE_BITS       16       // Bits por muestra
#define BUFFER_SIZE       512      // Tamaño del buffer de audio

// Tamaño de las características MFCC (debe coincidir con el modelo)
#define FEATURE_SLICE_SIZE 40

#endif // CONFIG_H

