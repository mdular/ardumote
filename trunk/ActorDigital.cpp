#include "WProgram.h"
#include "ActorDigital.h"

void ActorDigital::setup(char* sName, int nDigitalPin) {
  setName(sName);
  nPin = nDigitalPin;
  pinMode(nPin, OUTPUT);
  nDeviceTypeID = 5;
}

bool ActorDigital::exec(long p1) {
  if (p1>0) {
    digitalWrite(nPin, HIGH);
  } else {
    digitalWrite(nPin, LOW);
  }
  return true;
}
