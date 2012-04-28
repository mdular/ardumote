/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include "ActorModule.h"

void ActorModule::setName(char* name) {
  int i = 0;
  while (i<20 && i<strlen(name)) {
    sName[i] = name[i];
    i++;
  }
  sName[i] = '\0';
}

char* ActorModule::getName() {
  return sName;
}

bool ActorModule::exec(char* p) {
  Serial.println("Super Class Call to exec");
}

