/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include <Ethernet.h>
#include <ComModule.h>


class ComEthernetIRC: public ComModule {
  
  public:
    ComEthernetIRC();
    
    void setup(int nStatusPin);
    bool available();
    char* read();
    bool send(char* sCommand); 

  private:
 
    char sInBuffer[201];
    int  nInBufferPos;
    bool bAvailable;
    bool bReady;
    
    char* sReturnCommand;

    void connect();
    char myNick[11];
    void processIRCstr();
    void clearVars();
    void setStatus(bool status);
    int nStatusLEDPin;
};