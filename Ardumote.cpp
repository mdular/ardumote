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
printAvailableMemory();	  
	  processCommand(command);
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

void Ardumote::processCommand(char* s) {
  if (strlen(s) > 235) {
    return;  // command string is too long
  } else if (strlen(s) < 35) {
    return; // command string is too short
  }
  unsigned char strToHash[204];
  char* pch;
  long params[5];
  char* md5 = "01234567890123456789012345678901";
  md5[0] = '\0';
  int actorID = NULL;
  int paramCount = 0;
  
  for (int i = 0; i<strlen(s)-32; i++) {
    strToHash[i] = s[i];
  }
  strToHash[strlen(s)-32] = '\0';
  char* md5calc = MD5(strToHash, strlen(s)-32) ;
  
  
  // Protocol version
  pch = strtok (s, "*");
  if ( (pch != NULL) && (strcmp(pch, "1") ==0) ) {
  } else {
	Serial.println("version fail");
	return;
  }
  
  // Arduino Controler ID
  pch = strtok (NULL, "*");
  if ( (pch != NULL) && (atol(pch) == nArdumoteControllerID) ) { 
  } else {
	Serial.println("controllerID fail");
	return;
  }
  
  // ActorID
  pch = strtok (NULL, "*");
  if ( (pch != NULL) && (atoi(pch) < numActorModules) ) { 
    actorID = atoi(pch);
  } else {
	Serial.println("actorID fail");
	return;
  }
  
  // UTC
  pch = strtok (NULL, "*");
  if ( (pch != NULL)  ) { 
  } else {
	Serial.println("utc fail");
	return;
  }

  // Params + md5
  int i = 0;
  while (pch!=NULL)  {
     pch = strtok(NULL, "*");
	 if (strlen(pch) == 32) {
		strcpy(md5, pch);
		break;
	 } else if (strlen(pch) <=11 && i <= 4) {
		params[i] = atol(pch);
		paramCount++;
		Serial.println("param++");
	 } else {
       return;  // invalid params
	 }
	 i++;
  } 
  
  // md5
  if (strcmp(md5, md5calc) == 0) {
	Serial.println("md5 ok");
  } else {
  Serial.print(md5calc);
  Serial.print(" ");
	Serial.println("md5 failed");
	return;
  }
  
  if (paramCount == 5) {
	ActorModules[ actorID ]->exec( params[0], params[1], params[2], params[3], params[4] );
  } else if (paramCount == 4) {
	ActorModules[ actorID ]->exec( params[0], params[1], params[2], params[3] );
  } else if (paramCount == 3) {
	ActorModules[ actorID ]->exec( params[0], params[1], params[2] );
  } else if (paramCount == 2) {
	ActorModules[ actorID ]->exec( params[0], params[1] );
  } else if (paramCount == 1) {
	ActorModules[ actorID ]->exec( params[0] );
  } else {
    
  }
}


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
  for (int i = 0; i<32; i++) {
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




void Ardumote::printAvailableMemory() {
  int size = 2048; // Use 2048 with ATmega328
  byte *buf;

  while ((buf = (byte *) malloc(--size)) == NULL)
    ;

  free(buf);
  Serial.print("Memory: ");
  Serial.println(size);
}
