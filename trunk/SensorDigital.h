#include "WProgram.h"
#include <SensorModule.h>

class SensorDigital: public SensorModule {
  
  public:
    void setup(int nDigitalPin, unsigned int nIntervalSeconds);
    bool available();
    long getValue();

  private:
    unsigned int nIntervalMilliSeconds;
    int nPin;
    long nLastAvailable;
};