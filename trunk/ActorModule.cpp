#include "Arduino.h"
#include "ActorModule.h"

void ActorModule::setName(char* name) {
  int i = 0;
  while (i<10 && i<strlen(name)) {
    sName[i] = name[i];
    i++;
  }
  sName[i] = '\0';
}

char* ActorModule::getName() {
  return sName;
}

bool ActorModule::exec(long p1) {
  Serial.println("Super Class Call to exec (1)");
}

bool ActorModule::exec(long p1, long p2) {
  Serial.println("Super Class Call to exec (2)");
}

bool ActorModule::exec(long p1, long p2, long p3) {
  Serial.println("Super Class Call to exec (3)");
}

bool ActorModule::exec(long p1, long p2, long p3, long p4) {
  Serial.println("Super Class Call to exec (4)");
}

bool ActorModule::exec(long p1, long p2, long p3, long p4, long p5) {
  Serial.println("Super Class Call to exec (5)");
}
