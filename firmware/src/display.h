#pragma once

#include <U8g2lib.h>

#include "wiring.h"

U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, DISPLAY_SCL_PIN, DISPLAY_SDA_PIN, /* reset=*/U8X8_PIN_NONE);

#define MAX_DISPLAY_BUFFER_SIZE 11 // characters + null terminator
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

void setupDisplay()
{
    u8g2.begin();
}

void updateTimerDisplay(int totalSeconds)
{
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    // Clear only the timer area
    u8g2.setDrawColor(0);
    u8g2.drawBox(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

    u8g2.setDrawColor(1);
    u8g2.setCursor(0, 0);
    u8g2.printf("%1d:%02d", minutes, seconds);
}

void updateWeightDisplay(float weight)
{
    char weightStr[6];
    snprintf(weightStr, sizeof(weightStr), "%.1f", weight);

    // Clear only the weight area
    u8g2.setDrawColor(0);
    u8g2.drawBox(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    u8g2.setDrawColor(1);
    u8g2.setCursor(0, SCREEN_WIDTH - u8g2.getStrWidth(weightStr) - 2); // right aligned + a few pixels
    u8g2.print(weightStr);
}

void updateDisplay()
{
    // u8g2.sendBuffer();
}

float getWeight()
{
    // Replace this with the actual code to read the weight
    return random(0, 1000) / 10.0; // Example: Generate a random weight for testing
}
