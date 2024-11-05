#ifndef ESP32_SERVER_H
#define ESP32_SERVER_H

#include <Arduino.h>
#include <WebServer.h>

// Inicia el modo AP y el servidor HTTP
void startAPMode();

// Detiene el modo AP y el servidor HTTP
void stopAPMode();

// Maneja las solicitudes de los clientes
void handleClientRequests();

#endif // ESP32_SERVER_H
