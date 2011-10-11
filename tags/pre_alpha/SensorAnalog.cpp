#include "SensorAnalog.h"

void SensorAnalog::setup(char* sName, int nAnalogPin, unsigned int nSeconds) {
  setName(sName);
  nPin = nAnalogPin;
  pinMode(nPin, INPUT);
  nIntervalMilliSeconds = nSeconds*1000;
  nDeviceTypeID = 1;
}

bool SensorAnalog::available() {
  return (millis()-nLastAvailable) >= nIntervalMilliSeconds;
}

long SensorAnalog::getValue() {
  long value = 0;
  for (int i = 0; i<10; i++) {
    value += analogRead(nPin);
  }
  nLastAvailable = millis();
  return round(value/10);
}