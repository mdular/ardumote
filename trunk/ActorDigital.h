#include <ActorModule.h>

class ActorDigital : public ActorModule {
  
  public:
    bool exec(long p1);
    void setup(char* sName, int nDigitalPin);
    
  private:
    int nPin;

};
