// volume.h
#ifndef VOLUME_H
#define VOLUME_H

#include <Arduino.h>

void initVolumeControl();
void increaseVolume();
void decreaseVolume();
void saveVolume();
void loadVolume();
int getVolumeLevel();

#endif // VOLUME_H
