#pragma once

#include <Bounce2.h>
#include <Arduino.h>

#include "wiring.h"

const int BOUNCE_INTERVAL = 5;

unsigned long buttonPressStartTime = 0;
bool buttonPressed = false;
const unsigned long shortPressDuration = 1000; // 1 second
const unsigned long longPressDuration = 3000;  // 3 seconds

Bounce2::Button powerButton = Bounce2::Button();
Bounce2::Button timerButton = Bounce2::Button();

void setupButtons()
{
    powerButton.attach(POWER_BUTTON_PIN, INPUT_PULLUP);
    timerButton.attach(TIMER_BUTTON_PIN, INPUT_PULLUP);

    powerButton.interval(BOUNCE_INTERVAL);
    timerButton.interval(BOUNCE_INTERVAL);

    powerButton.setPressedState(HIGH);
    timerButton.setPressedState(HIGH);
}

void handlePowerButton()
{
    bool currentState = powerButton.pressed();

    Serial.print("Current state: ");
    Serial.println(currentState);

    if (currentState && !buttonPressed)
    {
        buttonPressed = true;
        buttonPressStartTime = millis();
    }
    else if (!currentState && buttonPressed)
    {
        unsigned long pressDuration = millis() - buttonPressStartTime;
        buttonPressed = false;

        if (pressDuration < shortPressDuration)
        {
            scale.tare();
        }
        else if (pressDuration >= longPressDuration)
        {
            enterLightSleep();
        }
    }
}
