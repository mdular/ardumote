#include "WProgram.h"
#include "ActorAnalog.h"

ActorAnalog::ActorAnalog() {
  
}

void ActorAnalog::setup(int nDigitalPin) {
  nPin = nDigitalPin;
  pinMode(nPin, OUTPUT);
}

bool ActorAnalog::exec(long p1) {
  if (p1>255) {
    analogWrite(nPin, 255);
  } else if (p1 <= 0) {
    analogWrite(nPin, 0);
  } else {
    analogWrite(nPin, p1);
  }
  return true;
}
