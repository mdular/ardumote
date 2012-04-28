/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include "ActorRCSwitch.h"

void ActorRCSwitch::setup(char* sName, int nDigitalPin) {
  setName(sName);
  pinMode(nDigitalPin, OUTPUT);
  digitalWrite(nDigitalPin, LOW);
  mySwitch.enableTransmit(nDigitalPin);
  Serial.print("Setup RC on pin ");
  Serial.println(nDigitalPin);
  mySwitch.setPulseLength(320);
  nDeviceTypeID = 6;
}

bool ActorRCSwitch::exec(char* p1) {
  long x = atol(p1);
  mySwitch.send(x, 24);
  return true;
}
