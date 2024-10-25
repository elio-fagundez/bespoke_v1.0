// mic.h
#ifndef MIC_H
#define MIC_H

#include <Arduino.h>

void initMicrophone();
void readMicrophone(int32_t *buffer, size_t len);

#endif // MIC_H
