#include "WProgram.h"
#include <ComModule.h>

class ComSerial : public ComModule {
  
  public:
    ComSerial();
    
    bool available();
    char* read();
    bool send(char* sCommand); 

  private:
    char sReturnCommand[50];
    int nCommandBufferPos;
    int bAvailable;
};