/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat �zg�r
    http://opensource.org/licenses/MIT
*/

#include <ActorModule.h>
#include <RCSwitch.h>

class ActorRCSwitch : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, int nDigitalPin);
    
  private:
    int nPin;
    RCSwitch mySwitch;

};
