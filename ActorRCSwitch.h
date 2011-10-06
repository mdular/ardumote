#include <ActorModule.h>
#include <RCSwitch.h>

class ActorRCSwitch : public ActorModule {
  
  public:
    bool exec(long p1);
    void setup(char* sName, int nDigitalPin);
    
  private:
    int nPin;
    RCSwitch mySwitch;

};
