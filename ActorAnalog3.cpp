#include "Arduino.h"
#include "ActorAnalog3.h"

void ActorAnalog3::setup(char* sName, int nAnalogPin1, int nAnalogPin2, int nAnalogPin3) {
  setName(sName);
  nPin1 = nAnalogPin1;
  nPin2 = nAnalogPin2;
  nPin3 = nAnalogPin3;
  pinMode(nPin1, OUTPUT);
  pinMode(nPin2, OUTPUT);
  pinMode(nPin3, OUTPUT);
  nDeviceTypeID = 7;
}

bool ActorAnalog3::exec(long p1, long p2, long p3) {
Serial.print(p1); Serial.print("-");
Serial.print(p2);Serial.print("-");
Serial.print(p3);
  if (p1>255) {
    analogWrite(nPin1, 255);
  } else if (p1 <= 0) {
    analogWrite(nPin1, 0);
  } else {
    analogWrite(nPin1, p1);
  }
  
  if (p2>255) {
    analogWrite(nPin2, 255);
  } else if (p2 <= 0) {
    analogWrite(nPin2, 0);
  } else {
    analogWrite(nPin2, p2);
  }

  if (p3>255) {
    analogWrite(nPin3, 255);
  } else if (p3 <= 0) {
    analogWrite(nPin3, 0);
  } else {
    analogWrite(nPin3, p3);
  }  
  
  return true;
}
