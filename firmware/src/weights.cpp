#include "weights.h"

HX711 scale1;
#ifdef DUAL_LOAD_CELL
HX711 scale2;
#endif

void readAndPrintWeight()
{
    if (scale1.is_ready()
#ifdef DUAL_LOAD_CELL
        && scale2.is_ready()
#endif
    )
    {
        long reading1 = scale1.read();
        Serial.print(scale1.get_units(), 1);

#ifdef DUAL_LOAD_CELL
        long reading2 = scale2.read();
        Serial.print(scale2.get_units(), 1);
#endif

        long totalWeight = reading1;
#ifdef DUAL_LOAD_CELL
        totalWeight += reading2;
#endif
        // Print the smoothed total weight
        Serial.print("Total Weight: ");
        Serial.println(totalWeight);
    }
    else
    {
        Serial.println("HX711 not ready yet.");
    }
}

void setupLoadCell()
{
    // Initialize and calibrate the scales
    scale1.begin(LOADCELL_DOUT_PIN_1, SCK);
    scale1.set_scale(calibration_factor);
    scale1.tare();

#ifdef DUAL_LOAD_CELL
    scale2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);
    scale2.set_scale(calibration_factor);
    scale2.tare();
#endif
}

void tareScale()
{
    Serial.println("Taring scale");
    // Add your tare logic here
}
