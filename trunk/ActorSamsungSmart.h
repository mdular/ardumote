/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include <ActorSamsungSmart.h>

class ActorSamsungSmart : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, byte myMac[6], byte remoteIp[4]);

  private:
    byte mac[6];
	byte ip[4];

};
