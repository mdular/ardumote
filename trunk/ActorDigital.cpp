#include "Arduino.h"
#include "ActorDigital.h"

void ActorDigital::setup(char* sName, int nDigitalPin) {
  setName(sName);
  nPin = nDigitalPin;
  pinMode(nPin, OUTPUT);
  nDeviceTypeID = 5;
}

bool ActorDigital::exec(char* p1) {
  if (atoi(p1)>0) {
    digitalWrite(nPin, HIGH);
  } else {
    digitalWrite(nPin, LOW);
  }
  Serial.print("P:");
  Serial.println(p1);
  return true;
}
