#include "Ardumote.h"
#include <Time.h>
#include "Arduino.h"
  
Ardumote::Ardumote() {
  numComModules    = 0;
  numSensorModules = 0;
  numActorModules  = 0;
  nProtocolVersion = 0;
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
      
      if (command[0] == 'c') {
      
        for (int k = 1; k<numSensorModules; k++) {
          char str[30];
          char* x;
          int j = 0;
          str[j++] = 's'; str[j++] = '*'; 
          x = n2chars(k);
          for (int i = 0; i<strlen(x); i++) {
            str[j++] = x[i];
          }
          str[j++] = '*';
          x = n2chars(SensorModules[k]->nDeviceTypeID);
          for (int i = 0; i<strlen(x); i++) {
            str[j++] = x[i];
          }
          str[j++] = '*';
          x = SensorModules[k]->getName();
          for (int i = 0; i<strlen(x); i++) {
            str[j++] = x[i];
          }
          str[j++] = '\0';
          
          sendValueToComModules(0, str);
        }
        for (int k = 1; k<numActorModules; k++) {
          char str[30];
          char* x;
          int j = 0;
          str[j++] = 'a'; str[j++] = '*';           
          x = n2chars(k);
          for (int i = 0; i<strlen(x); i++) {
            str[j++] = x[i];
          }
          str[j++] = '*';
          x = n2chars(ActorModules[k]->nDeviceTypeID);
          for (int i = 0; i<strlen(x); i++) {
            str[j++] = x[i];
          }
          str[j++] = '*';
          x = ActorModules[k]->getName();
          for (int i = 0; i<strlen(x); i++) {
            str[j++] = x[i];
          }
          str[j++] = '\0';
          
          sendValueToComModules(0, str);
        }

      } else {
        parseInCmd(command);
        processCommand();
      }
    }
  }
  // Sensor
  for (int i = 0; i<numSensorModules; i++) {
    if (SensorModules[i]->available()) {
      char* nV = SensorModules[i]->getValue();
      sendValueToComModules( i, nV );
    }
  }
}

void Ardumote::parseInCmd(char* sCmd) {
  for (int i = 0; i<10; i++) {
    inCommand[i][0] = '\0';
  }

  int nNumber = 0;
  char* pch;
  
  pch = strtok (sCmd, "*");
  while (pch != NULL)  {
    if (strlen(pch)<=32) {
      strcpy(inCommand[nNumber++], pch);
    } else {
      strcpy(inCommand[nNumber++], "invalid");
    }
    pch = strtok (NULL, "*");
  }
  
}

void Ardumote::processCommand() {
  long aParams[5];
  long nActorID;
  
  // Protocol Version
  if (atoi(inCommand[0]) != nProtocolVersion) {
    log("Version failed");
	Serial.println(inCommand[0]);
	Serial.println(nProtocolVersion);
    return;
  }
  
  // Arduino Controller ID
  if (atol(inCommand[1]) != nArdumoteControllerID) {
    log("ControllerID failed"); 
  }
  
  // ActorID
  nActorID = atoi(inCommand[2]);
  if (nActorID+1 > numActorModules) {
    log("ActorID failed");
    return;    
  }
  
  // UTC
  if (atol(inCommand[3]) == 0) {
    log("UTC failed");
    return;    
  }
  
  // Params
  int nParamCount = 0;
  while (nParamCount < 5 && inCommand[4+nParamCount+1][0] != '\0') {
    aParams[nParamCount] = atol( inCommand[4 + nParamCount] );
    nParamCount++;
  }
  
  // Auth
  char strToHash[250];
  int k = 0;
  for (int i = 0; i< 4+nParamCount; i++) {
    for (int j = 0; j<strlen(inCommand[i]); j++) {
      strToHash[k++] = inCommand[i][j];
    }
    strToHash[k++] = '*';
  }
  strToHash[k] = '\0';
  char* hash = this->getHash(strToHash);
  if (strcmp(hash, inCommand[nParamCount+4]) != 0) {
    log(hash);
    log(inCommand[nParamCount+4]);
    log("AuthString failed");
    return;
  }
 log("everything fine");
  
  if (nParamCount == 5) {
    ActorModules[ nActorID ]->exec( aParams[0], aParams[1], aParams[2], aParams[3], aParams[4] );
  } else if (nParamCount == 4) {
    ActorModules[ nActorID ]->exec( aParams[0], aParams[1], aParams[2], aParams[3] );
  } else if (nParamCount == 3) {
    ActorModules[ nActorID ]->exec( aParams[0], aParams[1], aParams[2] );
	log("3 params");
  } else if (nParamCount == 2) {
    ActorModules[ nActorID ]->exec( aParams[0], aParams[1] );
  } else if (nParamCount == 1) {
    ActorModules[ nActorID ]->exec( aParams[0] );
  } else {
    log("no parameters");
  }
  log("done");
}

void Ardumote::sendValueToComModules(int number, char* value) {

  char str[80];
  int j=0;
  
  char* x;

  // Protocol version
  str[j++] = (nProtocolVersion == 1 ? '1' : '2');   // ToDo: Obvious
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
  for (int i = 0; i<12 && value[i]!='\0'; i++) {
    str[j++] = value[i];
  }
  str[j++] = '*';
  str[j] = '\0';
  
  // + secret + md5
  char* hash = this->getHash(str);
  for (int i = 0; i<strlen(hash); i++) {
    str[j++] = hash[i];
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

char* Ardumote::getHash(char* strToHash) {
  return "Super";
}




void Ardumote::log(char* sMsg) {
  Serial.println(sMsg);
}