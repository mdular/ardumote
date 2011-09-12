#include <ActorModule.h>

class ActorDigital : public ActorModule {
  
  public:
    ActorDigital();
  
    bool exec(long p1);
    void setup(int nDigitalPin);
    
  private:
    int nPin;

};
