#include "WProgram.h"
#include "ActorDigital.h"

ActorDigital::ActorDigital() {
  
}

void ActorDigital::setup(int nDigitalPin) {
  nPin = nDigitalPin;
  pinMode(nPin, OUTPUT);
}

bool ActorDigital::exec(long p1) {
  if (p1>0) {
Serial.print("SET ");
Serial.print(nPin);
Serial.println(" HIGH");
    digitalWrite(nPin, HIGH);
  } else {
Serial.print("SET ");
Serial.print(nPin);
Serial.println(" LOW");
    digitalWrite(nPin, LOW);
  }
  return true;
}
