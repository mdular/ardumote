/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include <ComModule.h>

class ComSerial : public ComModule {
  
  public:
    ComSerial();
    void setup();    
    bool available();
    char* read();
    bool send(char* sCommand); 

  private:
    char sReturnCommand[200];
    int nCommandBufferPos;
    int bAvailable;
};