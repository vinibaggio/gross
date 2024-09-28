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
};

extern Scale scale;

void setupScale();
