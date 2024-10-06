#pragma once

// Button pins
const int POWER_BUTTON_PIN = 0;
const int TIMER_BUTTON_PIN = 1;

// Display pins
#define DISPLAY_SDA_PIN 8
#define DISPLAY_SCL_PIN 9

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN_1 20
#define LOADCELL_SCK_PIN 4 // Shared clock pin

#ifdef DUAL_LOAD_CELL
#define LOADCELL_DOUT_PIN_2 21
#endif

// Load cells default calibration factor
const float calibration_factor = -2000; // Adjust this value based on your calibration
