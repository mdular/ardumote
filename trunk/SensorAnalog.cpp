#include "SensorAnalog.h"

void SensorAnalog::setup(int nAnalogPin, unsigned int nSeconds) {
  nPin = nAnalogPin;
  pinMode(nPin, INPUT);
  nIntervalMilliSeconds = nSeconds*1000;
  nDeviceTypeID = 1;
}

bool SensorAnalog::available() {
  return (millis()-nLastAvailable) >= nIntervalMilliSeconds;
}

long SensorAnalog::getValue() {
  nLastAvailable = millis();
  return analogRead(nPin);
}