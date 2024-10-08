#pragma once

#include <Arduino.h>

#include "log.h"
#include "wiring.h"

const unsigned long shortPressDuration = 1000; // 1 second
const unsigned long longPressDuration = 3000;  // 3 seconds

inline void setupButtons()
{
    pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(TIMER_BUTTON_PIN, INPUT_PULLUP);
}

void handlePowerButton()
{
    bool powerState = digitalRead(POWER_BUTTON_PIN) == HIGH;
    bool timerState = digitalRead(TIMER_BUTTON_PIN) == HIGH;

    log("Current state - power ");
    log(powerState);
    log(" tare ");
    logln(timerState);

    if (powerState)
    {
        enterLightSleep();
    }
}
