#include "sd_card.h"

// Variable para rastrear si la SD está inicializada
static bool sdInitialized = false;

bool initSDCard() {
  // Iniciar la comunicación SPI con los pines definidos
  SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  // Intentar inicializar la tarjeta SD
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Error: No se pudo inicializar la tarjeta SD.");
    sdInitialized = false;
    return false;
  } else {
    Serial.println("Tarjeta SD inicializada correctamente.");
    sdInitialized = true;

    // Listar el contenido raíz de la tarjeta SD (opcional)
    /*Serial.println("Contenido de la tarjeta SD:");
    File root = SD.open("/");
    printDirectory(root, 0);
    root.close();*/

    return true;
  }
}

bool isSDCardInitialized() {
  return sdInitialized;
}

String readSDFile(const char* path) {
  if (!sdInitialized) {
    Serial.println("Error: La tarjeta SD no está inicializada.");
    return String();
  }

  Serial.print("Leyendo archivo: ");
  Serial.println(path);

  File file = SD.open(path);
  if (!file) {
    Serial.println("Error: No se pudo abrir el archivo para lectura.");
    return String();
  }

  String content;
  while (file.available()) {
    content += (char)file.read();
  }
  file.close();

  Serial.println("Lectura completada.");
  return content;
}

bool writeSDFile(const char* path, const char* data) {
  if (!sdInitialized) {
    Serial.println("Error: La tarjeta SD no está inicializada.");
    return false;
  }

  Serial.print("Escribiendo en archivo: ");
  Serial.println(path);

  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Error: No se pudo abrir el archivo para escritura.");
    return false;
  }

  if (file.print(data)) {
    Serial.println("Escritura exitosa.");
  } else {
    Serial.println("Error: Falló la escritura en el archivo.");
    file.close();
    return false;
  }
  file.close();
  return true;
}

bool createSDDir(const char* path) {
  if (!sdInitialized) {
    Serial.println("Error: La tarjeta SD no está inicializada.");
    return false;
  }

  Serial.print("Creando directorio: ");
  Serial.println(path);

  if (SD.mkdir(path)) {
    Serial.println("Directorio creado exitosamente.");
    return true;
  } else {
    Serial.println("Error: No se pudo crear el directorio.");
    return false;
  }
}

bool removeSDFile(const char* path) {
  if (!sdInitialized) {
    Serial.println("Error: La tarjeta SD no está inicializada.");
    return false;
  }

  Serial.print("Eliminando: ");
  Serial.println(path);

  if (SD.exists(path)) {
    if (SD.remove(path)) {
      Serial.println("Archivo eliminado exitosamente.");
      return true;
    } else {
      Serial.println("Error: No se pudo eliminar el archivo.");
      return false;
    }
  } else {
    Serial.println("Error: El archivo no existe.");
    return false;
  }
}

// Función auxiliar para listar el contenido de un directorio
void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No hay más archivos
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // Archivos, mostrar tamaño
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
