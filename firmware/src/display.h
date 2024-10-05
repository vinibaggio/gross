#pragma once

#include <U8x8lib.h>

#include "wiring.h"

U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(DISPLAY_SCL_PIN, DISPLAY_SDA_PIN);

void setupDisplay()
{
    u8x8.begin();
    u8x8.setFont(u8x8_font_8x13B_1x2_r);
    u8x8.setBusClock(400000);
    u8x8.draw1x2String(1, 1, "00:00    0.0G");
}

void updateTimerDisplay(int totalSeconds)
{
    static int previousTotal = 0;
    // fastest drawing is no drawing at all
    if (totalSeconds == previousTotal)
    {
        return;
    }

    int currentMinutes = totalSeconds / 60;
    int currentSeconds = totalSeconds % 60;

    int previousMinutes = previousTotal / 60;
    int previousSeconds = previousTotal % 60;

    const int clockStrLength = 5; // 00:00
    char previousClock[clockStrLength + 1];
    char currentClock[clockStrLength + 1];

    sprintf(previousClock, "%02d:%02d", previousMinutes, previousSeconds);
    sprintf(currentClock, "%02d:%02d", currentMinutes, currentSeconds);

    for (int i = 0; i <= clockStrLength; i++)
    {
        if (currentClock[i] != previousClock[i])
        {
            u8x8.draw1x2Glyph(i + 1, 1, currentClock[i]);
        }
    }

    previousSeconds = totalSeconds;
}

void updateWeightDisplay(float weight)
{
    static float previousWeight = 0.0f;
    // fastest drawing is no drawing at all
    if (weight == previousWeight)
    {
        return;
    }

    const int weightStrLength = 7; // 1000.0G
    char currentWeightStr[weightStrLength + 1];
    char previousWeightStr[weightStrLength + 1];

    sprintf(currentWeightStr, "%4.1fG", weight);
    sprintf(previousWeightStr, "%4.1fG", previousWeight);

    int rightAligned = u8x8.getCols() - weightStrLength;
    for (int i = 0; i < weightStrLength; i++)
    {
        if (currentWeightStr[i] != previousWeightStr[i])
        {
            u8x8.draw1x2Glyph(rightAligned + i, 1, currentWeightStr[i]);
        }
    }

    previousWeight = weight;
}
