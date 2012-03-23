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