#include <ActorModule.h>
#include <RCSwitch.h>

class ActorRCSwitch : public ActorModule {
  
  public:
    bool exec(long p1);
    void setup(int nDigitalPin);
    
  private:
    int nPin;
    RCSwitch mySwitch;

};
