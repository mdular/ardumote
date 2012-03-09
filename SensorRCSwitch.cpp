#include "SensorRCSwitch.h"

void SensorRCSwitch::setup(char* sName, int nInterrupt) {
  setName(sName);
  mySwitch.enableReceive(nInterrupt);
  nDeviceTypeID = 3;
  Serial.println("RCS setup done");
}

bool SensorRCSwitch::available() {
  if (mySwitch.available()) {
  Serial.println("avail.");
  }
  return mySwitch.available();
}

long SensorRCSwitch::getValue() {
  Serial.println("getv.");
  int val = mySwitch.getReceivedValue();
  mySwitch.resetAvailable();
  return val;
}