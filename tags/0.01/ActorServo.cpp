#include "Arduino.h"
#include "ActorServo.h"

void ActorServo::setup(char* sName, int nDigitalPin) {
  setName(sName);
  nPin = nDigitalPin;
  nDeviceTypeID = 8;
}

bool ActorServo::exec(long p1, long p2, long p3) {

  myservo.attach(nPin);
  delay(500);
  if (p1>179) {
    myservo.write(179);
  } else if (p1 <= 0) {
    myservo.write(0);
  } else {
    myservo.write(p1);
  }

  Serial.print("delay...");
  Serial.println(p3);
  delay(p3);

  
  if (p2>179) {
    myservo.write(179);
  } else if (p2 <= 0) {
    myservo.write(0);
  } else {
    myservo.write(p2);
  }
  delay(2000);
  myservo.detach();

  return true;
}

