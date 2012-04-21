#include <ActorModule.h>

class ActorAnalog : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, int nDigitalPin);

  private:
    int nPin;

};
