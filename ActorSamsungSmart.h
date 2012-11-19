/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include <Ethernet.h>
#include <ActorModule.h>
#include <Base64.h>

class ActorSamsungSmart : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName,  IPAddress server);

  private:
	IPAddress srv;

};
