/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "SensorRCSwitch.h"

void SensorRCSwitch::setup(char* sName, int nInterrupt) {
  setName(sName);
  mySwitch.enableReceive(nInterrupt);
  nDeviceTypeID = 3;
}

bool SensorRCSwitch::available() {
  return mySwitch.available();
}

char* SensorRCSwitch::getValue() {
  char* buf = "123456789012345"; 
  ltoa(mySwitch.getReceivedValue(), buf, 10);
  mySwitch.resetAvailable();
  return buf;
}