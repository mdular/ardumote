/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include <SensorModule.h>

class SensorDigital: public SensorModule {
  
  public:
    void setup(char* sName, int nDigitalPin, unsigned int nIntervalSeconds);
    bool available();
    char* getValue();

  private:
    unsigned int nIntervalMilliSeconds;
    int nPin;
    long nLastAvailable;
};