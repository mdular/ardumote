#include "WProgram.h"
#include "SensorModule.h"

long SensorModule::getValue() {
  Serial.println("Super Class Call to getValue");
}

bool SensorModule::available() {
  Serial.println("Super Class Call to available");
}