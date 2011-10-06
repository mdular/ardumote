#include "WProgram.h"
#include <SensorModule.h>

class SensorDigital: public SensorModule {
  
  public:
    void setup(char* sName, int nDigitalPin, unsigned int nIntervalSeconds);
    bool available();
    long getValue();

  private:
    unsigned int nIntervalMilliSeconds;
    int nPin;
    long nLastAvailable;
};