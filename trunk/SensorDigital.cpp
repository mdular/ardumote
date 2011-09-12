#include "SensorDigital.h"

SensorDigital::SensorDigital() {
  
}

void SensorDigital::setup(int nDigitalPin) {
  nPin = nDigitalPin;
  pinMode(nPin, INPUT);
}

void SensorDigital::setInterval(unsigned int nSeconds) {
  nIntervalMilliSeconds = nSeconds*1000;
}

bool SensorDigital::available() {
  return (millis()-nLastAvailable) >= nIntervalMilliSeconds;
}

long SensorDigital::getValue() {
  nLastAvailable = millis();
  return digitalRead(nPin);
}