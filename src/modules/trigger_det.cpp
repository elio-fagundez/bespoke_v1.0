#include "trigger_det.h"
#include "config.h"

#include <TensorFlowLite_ESP32.h>  // Librería para TensorFlow Lite en ESP32

// Incluir el modelo de TensorFlow Lite para detección de palabras clave
// #include "keyword_model.h"  // Archivo generado que contiene el modelo

// Variables para el modelo de TensorFlow Lite
tflite::MicroInterpreter* interpreter = nullptr;
tflite::MicroErrorReporter errorReporter;
tflite::AllOpsResolver resolver;
tflite::MicroAllocator* allocator = nullptr;
uint8_t tensorArena[10 * 1024];  // Arena de 10 KB para TensorFlow Lite

// Variable para indicar si se ha detectado el trigger
volatile bool triggerDetected = false;

void initTriggerDetection() {
    // Configurar el modelo de TensorFlow Lite
    const tflite::Model* model = tflite::GetModel(keyword_model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Error: Versión del modelo no compatible.");
        while (1);
    }

    // Crear el intérprete
    allocator = tflite::MicroAllocator::Create(tensorArena, sizeof(tensorArena), &errorReporter);
    interpreter = new tflite::MicroInterpreter(model, resolver, allocator, &errorReporter);

    // Asignar tensores
    interpreter->AllocateTensors();

    Serial.println("Modelo de TensorFlow Lite inicializado para detección de palabras clave.");
}

void processAudioForTrigger(int16_t* audioData, size_t dataSize) {
    // Procesar los datos de audio para extraer características
    // Esta es una simplificación; en una implementación real, se debe realizar extracción de características (MFCC)

    // Asumiendo que tenemos una función para extraer MFCC llamada extractMFCC()
    float mfccFeatures[FEATURE_SLICE_SIZE];
    extractMFCC(audioData, dataSize, mfccFeatures);

    // Preparar los datos de entrada para el modelo
    TfLiteTensor* input = interpreter->input(0);
    for (int i = 0; i < FEATURE_SLICE_SIZE; i++) {
        input->data.f[i] = mfccFeatures[i];
    }

    // Ejecutar el modelo
    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("Error al ejecutar el modelo de TensorFlow Lite.");
        return;
    }

    // Obtener el resultado
    TfLiteTensor* output = interpreter->output(0);
    float score = output->data.f[0];  // Asumiendo que el modelo tiene una salida

    // Determinar si se detectó la palabra clave
    if (score > TRIGGER_THRESHOLD) {
        triggerDetected = true;
        Serial.println("¡Palabra clave detectada: 'hey teddy'!");
    } else {
        triggerDetected = false;
    }
}

bool isTriggerDetected() {
    return triggerDetected;
}

// Función ficticia para extracción de MFCC (debe ser implementada)
void extractMFCC(int16_t* audioData, size_t length, float* mfccOut) {
    // Implementación de extracción de MFCC
    // Por simplicidad, se llenará con ceros
    for (int i = 0; i < FEATURE_SLICE_SIZE; i++) {
        mfccOut[i] = 0.0f;
    }
}
