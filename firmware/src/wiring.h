#pragma once

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN_1 3
#define LOADCELL_SCK_PIN 4 // Shared clock pin

#ifdef DUAL_LOAD_CELL
#define LOADCELL_DOUT_PIN_2 21
#endif

// Load cells default calibration factor
const float calibration_factor = -2000; // Adjust this value based on your calibration
