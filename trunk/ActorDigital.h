#include <ActorModule.h>

class ActorDigital : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, int nDigitalPin);
    
  private:
    int nPin;

};
