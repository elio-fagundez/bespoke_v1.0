// sd_card.h
#pragma once
#include "FS.h"
#include "SD.h"

bool initSDCard();

void writeFile(fs::FS &fs, const char *path, const char *message);
