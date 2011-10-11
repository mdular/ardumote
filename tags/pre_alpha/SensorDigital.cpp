#include "SensorDigital.h"

void SensorDigital::setup(char* sName, int nDigitalPin, unsigned int nSeconds) {
  setName(sName);
  nPin = nDigitalPin;
  pinMode(nPin, INPUT);
  nIntervalMilliSeconds = nSeconds*1000;
  nDeviceTypeID = 2;
}

bool SensorDigital::available() {
  return (millis()-nLastAvailable) >= nIntervalMilliSeconds;
}

long SensorDigital::getValue() {
  nLastAvailable = millis();
  return digitalRead(nPin);
}