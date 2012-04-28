/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

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

char* SensorAnalog::getValue() {
  long value = 0;
  for (int i = 0; i<10; i++) {
    value += analogRead(nPin);
  }
  nLastAvailable = millis();
  char* buf = "123456789012345"; 
  ltoa(round(value/10), buf, 10);
  return buf;
}