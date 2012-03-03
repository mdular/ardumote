#include "Arduino.h"
#include <SensorModule.h>

class SensorAnalog : public SensorModule {
  
  public:
    void setup(char* sName, int nAnalogPin, unsigned int nIntervalSeconds);
    bool available();
    long getValue();

  private:
    unsigned int nIntervalMilliSeconds;
    int nPin;
    long nLastAvailable;

};