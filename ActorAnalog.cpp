#include "Arduino.h"
#include "ActorAnalog.h"

void ActorAnalog::setup(char* sName, int nDigitalPin) {
  setName(sName);
  nPin = nDigitalPin;
  pinMode(nPin, OUTPUT);
  nDeviceTypeID = 4;
}

bool ActorAnalog::exec(char* p) {
  int p1 = atoi(p);
  if (p1>255) {
    analogWrite(nPin, 255);
  } else if (p1 <= 0) {
    analogWrite(nPin, 0);
  } else {
    analogWrite(nPin, p1);
  }
  return true;
}
