// spk.h
#ifndef SPK_H
#define SPK_H

#include <Arduino.h>
#include "config.h"
#include "pins.h" 

void initSpeaker(const char* streamURL); // Un solo argumento
void loopSpeaker();

#endif // SPK_H



