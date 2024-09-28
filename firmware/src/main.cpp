#include <Arduino.h>
#include <Bounce2.h>

#include "scale.h"
#include "sleep.h"
#include "display.h"

const int POWER_BUTTON_PIN = 0;
const int TIMER_BUTTON_PIN = 1;
const int BOUNCE_INTERVAL = 5;

unsigned long buttonPressStartTime = 0;
bool buttonPressed = false;
const unsigned long shortPressDuration = 1000; // 1 second
const unsigned long longPressDuration = 3000;  // 3 seconds

Bounce2::Button powerButton = Bounce2::Button();
Bounce2::Button timerButton = Bounce2::Button();

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

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Serial is ready to accept input");

  Serial.println("Setting up buttons");

  powerButton.attach(POWER_BUTTON_PIN, INPUT_PULLUP);
  timerButton.attach(TIMER_BUTTON_PIN, INPUT_PULLUP);

  powerButton.interval(BOUNCE_INTERVAL);
  timerButton.interval(BOUNCE_INTERVAL);

  powerButton.setPressedState(HIGH);
  timerButton.setPressedState(HIGH);

  setupScale();
  setupDisplay();

  // setupSleep(powerButton);
}

int seconds = 0;

void loop()
{

  seconds++;

  displayTimerAndWeight(seconds, seconds * 1.0f);

  handlePowerButton();
  // readAndPrintWeight();
  delay(1000);
}

// // #include <NimBLEDevice.h>
// // #include "HX711.h"

// // // HX711 circuit wiring
// // #define LOADCELL_DOUT_PIN_1 18
// // #define LOADCELL_SCK_PIN 19 // Shared clock pin
// // #define LOADCELL_DOUT_PIN_2 21

// // HX711 scale1;
// // HX711 scale2;

// // const int numReadings = 10; // Number of readings to average for smoothing
// // long readings[numReadings]; // Array to store readings
// // int readIndex = 0;          // Index of the current reading
// // long total = 0;             // Running total
// // long average = 0;           // The average

// // NimBLECharacteristic* pWeightCharacteristic;

// // void setup() {
// //   Serial.begin(115200);

// //   // Initialize the scales
// //   scale1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN);
// //   scale2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN);

// //   // Initialize the readings array
// //   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
// //     readings[thisReading] = 0;
// //   }

// //   // Initialize BLE
// //   NimBLEDevice::init("WeightScale");

// //   // Create BLE Server
// //   NimBLEServer *pServer = NimBLEDevice::createServer();

// //   // Create BLE Service
// //   NimBLEService *pService = pServer->createService("180F"); // Custom service UUID

// //   // Create BLE Characteristic
// //   pWeightCharacteristic = pService->createCharacteristic(
// //                             "2A6E", // Custom characteristic UUID
// //                             NIMBLE_PROPERTY::READ |
// //                             NIMBLE_PROPERTY::NOTIFY
// //                           );

// //   // Start the service
// //   pService->start();

// //   // Start advertising
// //   pServer->getAdvertising()->start();
// //   Serial.println("BLE device is now advertising");
// // }

// // void loop() {
// //   // Read values from the load cells
// //   if (scale1.is_ready() && scale2.is_ready()) {
// //     long reading1 = scale1.read();
// //     long reading2 = scale2.read();
// //     long totalWeight = reading1 + reading2;

// //     // Subtract the last reading
// //     total = total - readings[readIndex];
// //     // Add the current reading
// //     readings[readIndex] = totalWeight;
// //     total = total + readings[readIndex];
// //     // Advance to the next position in the array
// //     readIndex = (readIndex + 1) % numReadings;

// //     // Calculate the average
// //     average = total / numReadings;

// //     // Convert average to float for BLE transmission
// //     float smoothedWeight = (float)average;

// //     // Update the BLE characteristic
// //     pWeightCharacteristic->setValue(smoothedWeight);
// //     pWeightCharacteristic->notify();

// //     // Print the smoothed weight
// //     Serial.print("Smoothed Total Weight: ");
// //     Serial.println(smoothedWeight);
// //   } else {
// //     Serial.println("HX711 not found.");
// //   }

// //   delay(1000); // Adjust delay as needed
// // }
