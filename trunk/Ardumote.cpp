#include "Ardumote.h"

  
Ardumote::Ardumote() {
  numComModules    = 0;
  numSensorModules = 0;
  numActorModules  = 0;
}  

void Ardumote::addComModule(ComModule* m) {
  if (numComModules < 3 ) {
    ComModules[numComModules++] = m;
  }
}

void Ardumote::addSensorModule(SensorModule* m) {
  if (numSensorModules < 5) {
    SensorModules[numSensorModules++] = m;
  }
}
void Ardumote::addActorModule(ActorModule* m) {
  if (numActorModules < 5) {
    ActorModules[numActorModules++] = m;
  }
}

void Ardumote::loop() {
  // Com
  for (int i = 0; i<numComModules; i++) {
    if (ComModules[i]->available() ) {
      char* command = ComModules[i]->read();
      Serial.print("Command (Mod #");
      Serial.print(i);
      Serial.print("): ");
      Serial.println( command );
    }
  }
  // Sensor
  for (int i = 0; i<numSensorModules; i++) {
    if (SensorModules[i]->available()) {
      int nV = SensorModules[i]->getValue();
      sendValueToComModules( i, nV );
    }
  }  
}
/*
void Ardumote::processCommand(char* s) {
}
*/

void Ardumote::sendValueToComModules(int number, long nV) {
  for (int i = 0; i<numComModules; i++) {
    char* v = "123456789012345"; 
    ltoa(nV, v, 10);
    ComModules[i]->send(v);
  }
}
