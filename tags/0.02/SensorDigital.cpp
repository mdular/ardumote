/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

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

char* SensorDigital::getValue() {
  nLastAvailable = millis();
  if (digitalRead(nPin)) {
    return "1";
  } else {
	return "0";
  }
}