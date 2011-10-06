#include "WProgram.h"
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