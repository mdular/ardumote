#include "WProgram.h"
#include <ComModule.h>
#include <SensorModule.h>
#include <ActorModule.h>

class Ardumote {

  public:
    Ardumote();
    void addComModule(ComModule* m);
    void addSensorModule(SensorModule* m);
    void addActorModule(ActorModule* m);
    void loop();
    void sendValueToComModules(int number, long value);
    
  private:
    ComModule*    ComModules[3];
    SensorModule* SensorModules[5];
    ActorModule*  ActorModules[5];
    uint8_t numComModules;
    uint8_t numSensorModules;
    uint8_t numActorModules;
};
