#pragma once

#include <Arduino.h>

#ifdef DEBUG
#define log(...) \
    if (Serial)  \
        Serial.print(__VA_ARGS__);

#define logf(...) \
    if (Serial)   \
        Serial.printf(__VA_ARGS__);

#define logln(...) \
    if (Serial)    \
        Serial.println(__VA_ARGS__);
#else
#define log(...) ;
#define logf(...) ;
#define logln(...) ;
#endif
