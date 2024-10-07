#include <Arduino.h>
#include <esp_sleep.h>

#include "log.h"
#include "scale.h"
#include "sleep.h"

void enterLightSleep()
{
    logln("Entering deep sleep");
    const esp_err_t err = esp_light_sleep_start();
    if (err != ESP_OK)
    {
        log("Error: ");
        logln(err);
    }
    else
    {
        logln("Woken up from light sleep");
    }
}

void wakeUpRoutine()
{
    logln("Waking up from deep sleep");
    scale.tare();
}

// Add this to your setup() function
void setupWakeUpRoutine()
{
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    log("Wakeup reason: ");
    logln(wakeup_reason);
    if (wakeup_reason == ESP_SLEEP_WAKEUP_GPIO)
    {
        wakeUpRoutine();
    }
}

void setupSleep(int powerButton)
{
    pinMode(powerButton, INPUT_PULLUP);
    gpio_wakeup_enable((gpio_num_t)powerButton, GPIO_INTR_HIGH_LEVEL);
    esp_sleep_enable_gpio_wakeup();
}
