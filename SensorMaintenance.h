/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include <SensorModule.h>

class SensorMaintenance: public SensorModule {
  
  public:
    void setup();
    bool available();
    char* getValue();

  private:
    long nLastAvailable;

};