#include "WProgram.h"
#include <SensorModule.h>

class SensorAnalog : public SensorModule {
  
  public:
    SensorAnalog();
    
    bool available();
    long getValue();

    void setup(int nAnalogPin);
    void setInterval(unsigned int nSeconds);

  private:
    unsigned int nIntervalMilliSeconds;
    int nPin;
    long nLastAvailable;
};