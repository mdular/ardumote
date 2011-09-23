#include "Ardumote.h"
#include <Time.h>
#include <MD5.c>
#include "WProgram.h"
  
Ardumote::Ardumote() {
  numComModules    = 0;
  numSensorModules = 0;
  numActorModules  = 0;
}

void Ardumote::setup(long nControllerID, char* secret) {
  nArdumoteControllerID = nControllerID;
  sSecret = secret;
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

void Ardumote::sendValueToComModules(int number, long value) {
  char str[80];
  int j=0;
  
  char* x;

  // Protocol version
  str[j++] = '1';
  str[j++] = '*';
  
  // Arduino Controler ID
  x = n2chars(nArdumoteControllerID);
  for (int i = 0; i<strlen(x); i++) {
    str[j++] = x[i];
  }
  str[j++] = '*';
  
  // SensorID
  x = n2chars(number);
  for (int i = 0; i<strlen(x); i++) {
    str[j++] = x[i];
  }
  str[j++] = '*';
  
  // Time
  x = n2chars((long)now());
  for (int i = 0; i<strlen(x); i++) {
    str[j++] = x[i];
  }
  str[j++] = '*';

  // Value
  x = n2chars(value);
  for (int i = 0; i<strlen(x); i++) {
    str[j++] = x[i];
  }
  str[j++] = '*';
  str[j] = '\0';
  
  // + secret + md5
  unsigned char strToHash[80];
  int k;
  for (int i = 0; i<strlen(str); i++) {
    strToHash[i] = str[i];
    k=i;
  }
  k++;
  
  for (int i = 0; i<strlen(sSecret); i++) {
    strToHash[k+i] = sSecret[i];
  }
  x = MD5(strToHash, k+strlen(sSecret));
  for (int i = 0; i<strlen(x); i++) {
    str[j++] = x[i];
  }
  str[j] = '\0';
  
  // Send it :)
  for (int i = 0; i<numComModules; i++) {
    ComModules[i]->send(str);
  }

}

char* Ardumote::n2chars(long number) {
    char* v = "123456789012345"; 
    ltoa(number, v, 10);
    return v;
}

char* Ardumote::n2chars(int number) {
    char* v = "123456789012345"; 
    ltoa(number, v, 10);
    return v;
}
