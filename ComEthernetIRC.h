#include "WProgram.h"
#include <Ethernet.h>
#include <ComModule.h>


class ComEthernetIRC: public ComModule {
  
  public:
    ComEthernetIRC();
    
    void setup(byte* mac, byte* ip, byte* remoteIp);
    
    bool available();
    char* read();
    bool send(char* sCommand); 

  private:
    //Client client;
    byte serverIP[4];
    char sReturnCommand[201];
    int nCommandBufferPos;
    bool bAvailable;
    void connect();
};