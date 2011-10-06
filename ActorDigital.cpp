#include "WProgram.h"
#include "ActorDigital.h"

void ActorDigital::setup(int nDigitalPin) {
  nPin = nDigitalPin;
  pinMode(nPin, OUTPUT);
}

bool ActorDigital::exec(long p1) {
  if (p1>0) {
    digitalWrite(nPin, HIGH);
  } else {
    digitalWrite(nPin, LOW);
  }
  return true;
}
