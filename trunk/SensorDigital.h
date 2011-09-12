#include "WProgram.h"
#include <SensorModule.h>

class SensorDigital: public SensorModule {
  
  public:
    SensorDigital();

    bool available();
    long getValue();

    void setup(int nDigitalPin);
    void setInterval(unsigned int nSeconds);

  private:
    unsigned int nIntervalMilliSeconds;
    int nPin;
    long nLastAvailable;
};