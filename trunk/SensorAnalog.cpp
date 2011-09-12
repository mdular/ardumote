#include "SensorAnalog.h"

SensorAnalog::SensorAnalog() {
  
}

void SensorAnalog::setup(int nAnalogPin) {
  nPin = nAnalogPin;
  pinMode(nPin, INPUT);
}

void SensorAnalog::setInterval(unsigned int nSeconds) {
  nIntervalMilliSeconds = nSeconds*1000;
}

bool SensorAnalog::available() {
  return (millis()-nLastAvailable) >= nIntervalMilliSeconds;
}

long SensorAnalog::getValue() {
  nLastAvailable = millis();
  return analogRead(nPin);
}