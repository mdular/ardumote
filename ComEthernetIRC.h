#include "WProgram.h"
#include <Ethernet.h>
#include <ComModule.h>


class ComEthernetIRC: public ComModule {
  
  public:
    ComEthernetIRC();
    
    void setup();
    bool available();
    char* read();
    bool send(char* sCommand); 

  private:
    char sInBuffer[201];
    int  nInBufferPos;
    bool bAvailable;
    
    char* sReturnCommand;

    void connect();
    char myNick[11];
    void processIRCstr();
    void clearVars();

};