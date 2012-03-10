#include "Arduino.h"
#include "SensorModule.h"

void SensorModule::setName(char* name) {
  int i = 0;
  while (i<10 && i<strlen(name)) {
    sName[i] = name[i];
    i++;
  }
  sName[i] = '\0';
}

char* SensorModule::getName() {
  return sName;
}

char* SensorModule::getValue() {
  Serial.println("Super Class Call to getValue");
}

bool SensorModule::available() {
  Serial.println("Super Class Call to available");
}