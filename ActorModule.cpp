#include "WProgram.h"
#include "ActorModule.h"

bool ActorModule::exec(long p1) {
  Serial.println("Super Class Call to exec");
}

bool ActorModule::exec(long p1, long p2) {
  Serial.println("Super Class Call to exec");
}

bool ActorModule::exec(long p1, long p2, long p3) {
  Serial.println("Super Class Call to exec");
}

bool ActorModule::exec(long p1, long p2, long p3, long p4) {
  Serial.println("Super Class Call to exec");
}

bool ActorModule::exec(long p1, long p2, long p3, long p4, long p5) {
  Serial.println("Super Class Call to exec");
}
