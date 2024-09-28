#pragma once

#include <U8g2lib.h>

#include "wiring.h"

U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, DISPLAY_SCL_PIN, DISPLAY_SDA_PIN, /* reset=*/U8X8_PIN_NONE);

#define MAX_DISPLAY_BUFFER_SIZE 11 // characters + null terminator

void setupDisplay()
{
    u8g2.begin();
}

void fillBuffer(char *buffer, char ch, int count)
{
    for (int i = 0; i < count; i++)
    {
        buffer[i] = ch;
    }
}

void displayTimerAndWeight(int timerSeconds, float weight)
{
    int minutes = timerSeconds / 60;
    int seconds = timerSeconds % 60;

    char weightStr[6];
    char time[4];
    snprintf(weightStr, sizeof(weightStr), "%.1f", weight);

    char spaces[5];

    fillBuffer(spaces, ' ', MAX_DISPLAY_BUFFER_SIZE - 4 /* timer */ - 1 /* null */ - strlen(weightStr));
    // Serial.printf("Spaces: %s\n", strlen(spaces));

    char buffer[MAX_DISPLAY_BUFFER_SIZE];

    snprintf(buffer, sizeof(buffer), "%1d:%02d%s%s", minutes, seconds, spaces, weightStr);

    u8g2.firstPage();

    do
    {
        u8g2.setFont(u8g2_font_VCR_OSD_mu);
        u8g2.drawStr(0, 28, buffer);
    } while (u8g2.nextPage());
}
