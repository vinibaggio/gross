#pragma once

#include "HX711.h"

// Define build profiles
// HX711 circuit wiring
#define LOADCELL_DOUT_PIN_1 3
#define LOADCELL_SCK_PIN 4 // Shared clock pin

#ifdef DUAL_LOAD_CELL
#define LOADCELL_DOUT_PIN_2 21
#endif

extern HX711 scale1;
#ifdef DUAL_LOAD_CELL
extern HX711 scale2;
#endif

const float calibration_factor = -2000; // Adjust this value based on your calibration

void readAndPrintWeight();
void setupLoadCell();
void tareScale();
