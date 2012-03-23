#include "Arduino.h"
#include <SensorModule.h>
#include <RCSwitch.h>

class SensorRCSwitch: public SensorModule {
  
  public:
    void setup(char* sName, int nInterrupt);
    bool available();
    char* getValue();
	
  private:
    RCSwitch mySwitch;
};