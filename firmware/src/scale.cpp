#include "log.h"
#include "scale.h"
#include "wiring.h"

Scale scale;
HX711 loadCell1;
#ifdef DUAL_LOAD_CELL
HX711 loadCell2;
#endif

void Scale::addLoadCell(HX711 *cell, int pin, int sckPin)
{
    cell->begin(pin, sckPin);
    loadCells.push_back(cell);
}

void Scale::setCalibrationFactor(float factor)
{
    for (auto cell : this->loadCells)
    {
        cell->set_scale(factor);
    }
}

// void Scale::sleep()
// {
//     for (auto cell : this->loadCells)
//     {
//         cell->power_down();
//     }
// }

void Scale::tare()
{
    for (auto cell : loadCells)
    {
        cell->tare();
    }
}

bool Scale::isReady()
{
    for (auto cell : loadCells)
    {
        if (!cell->is_ready())
        {
            return false;
        }
    }
    return true;
}

float Scale::getTotalWeight()
{
    float totalWeight = 0;
    for (auto cell : loadCells)
    {
        log("Reading scale: ");
        logln(cell->get_units());
        totalWeight += cell->get_units();
    }
    return totalWeight;
}

void setupScale()
{
    scale.addLoadCell(&loadCell1, LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);

#ifdef DUAL_LOAD_CELL
    scale.addLoadCell(&loadCell2, LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);
#endif

    scale.setCalibrationFactor(calibration_factor);
    scale.tare();
}

void tareScale()
{
    logln("Taring scale");
    scale.tare();
}
