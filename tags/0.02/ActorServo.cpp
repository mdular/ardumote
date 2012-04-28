/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include "ActorServo.h"

void ActorServo::setup(char* sName, int nDigitalPin) {
  setName(sName);
  nPin = nDigitalPin;
  nDeviceTypeID = 8;
}

bool ActorServo::exec(char* p1) {
  int params[3];
  int paramCount = 0;
  char* pch;
  
  pch = strtok (p1, ",");
  while (pch != NULL)  {
    params[paramCount++] = atoi(pch);
    Serial.print(pch);
    Serial.print(" ");
    Serial.println(params[paramCount-1]);
    pch = strtok (NULL, ",");    
  }
 
  
  myservo.attach(nPin);
  delay(500);
  if (params[0]>179) {
    myservo.write(179);
  } else if (params[0] <= 0) {
    myservo.write(0);
  } else {
    myservo.write(params[0]);
  }

  Serial.print("delay...");
  Serial.println(params[1]);
  delay(params[1] * 1000);

  
  if (params[2]>179) {
    myservo.write(179);
  } else if (params[2] <= 0) {
    myservo.write(0);
  } else {
    myservo.write(params[2]);
  }
  delay(2000);
  myservo.detach();

  return true;
  
  
}

