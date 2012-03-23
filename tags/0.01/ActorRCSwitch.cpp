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

bool ActorRCSwitch::exec(long p1) {
  mySwitch.send(p1, 24);
  return true;
}
