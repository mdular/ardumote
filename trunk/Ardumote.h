#ifndef ardumote_h
#define ardumote_h

#include "WProgram.h"
#include <ComModule.h>
#include <SensorModule.h>
#include <ActorModule.h>

#define DEBUG true
 
class Ardumote {

  public:
    Ardumote();
    void setup(long nControllerID, char* secret);
    void addComModule(ComModule* m);
    void addSensorModule(SensorModule* m);
    void addActorModule(ActorModule* m);
    void loop();

  protected:
    virtual char* getHash(char* strToHash);

    void sendValueToComModules(int number, long value);
    void processCommand();
  
    ComModule*    ComModules[3];
    SensorModule* SensorModules[5];
    ActorModule*  ActorModules[5];
    
    int numComModules;
    int numSensorModules;
    int numActorModules;
    
    long nArdumoteControllerID;
    char* sSecret;
    
    char inCommand[10][33];
  
    char* n2chars(long number);
    char* n2chars(int number);
    void printAvailableMemory();
    void log(char* sMsg);
    void parseInCmd(char* command);
};


#endif