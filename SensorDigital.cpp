#include "SensorDigital.h"

void SensorDigital::setup(int nDigitalPin, unsigned int nSeconds) {
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