/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat �zg�r
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include <Ethernet.h>
#include <ComModule.h>

class ComEthernetHTTP: public ComModule {
  
  public:
    ComEthernetHTTP();
    
    void setup(byte* mac, byte* ip, byte* remoteIp);
    
    bool available();
    char* read();
    bool send(char* sCommand); 

  private:
    byte serverIP[4];
    char sReturnCommand[50];
};