#include "WProgram.h"
#include "ActorRCSwitch.h"

void ActorRCSwitch::setup(int nDigitalPin) {
  mySwitch.enableTransmit(nDigitalPin);
  mySwitch.setPulseLength(320);
}

bool ActorRCSwitch::exec(long p1) {
  mySwitch.send(p1, 24);
  return true;
}
