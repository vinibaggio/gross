#pragma once

#include <vector>
#include <HX711.h>

class Scale
{
private:
    std::vector<HX711 *> loadCells;

public:
    void addLoadCell(HX711 *cell, int pin, int sckPin);
    void setCalibrationFactor(float factor);
    void tare();
    bool isReady();
    float getTotalWeight();
    void sleep();
    void wake();
    // TODO move this to a lifecycle management interface
};

extern Scale scale;

void setupScale();
