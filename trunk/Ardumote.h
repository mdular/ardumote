#include "WProgram.h"
#include <ComModule.h>
#include <SensorModule.h>
#include <ActorModule.h>
 
class Ardumote {

  public:
    Ardumote();
    void setup(long nControllerID, char* secret);
    void addComModule(ComModule* m);
    void addSensorModule(SensorModule* m);
    void addActorModule(ActorModule* m);
    void loop();
    
  private:
    void sendValueToComModules(int number, long value);
	void processCommand(char* command);
	
    ComModule*    ComModules[3];
    SensorModule* SensorModules[5];
    ActorModule*  ActorModules[5];
    uint8_t numComModules;
    uint8_t numSensorModules;
    uint8_t numActorModules;
    long nArdumoteControllerID;
    char* sSecret;
	
    char* n2chars(long number);
    char* n2chars(int number);
	void printAvailableMemory();
};
