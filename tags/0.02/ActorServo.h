/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat �zg�r
    http://opensource.org/licenses/MIT
*/

#include <ActorModule.h>
#include <Servo.h> 

class ActorServo : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, int nDigitalPin);

  private:
    int nPin;
	Servo myservo;

};
