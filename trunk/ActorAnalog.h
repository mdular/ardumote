#include <ActorModule.h>

class ActorAnalog : public ActorModule {
  
  public:
    bool exec(long p1);
    void setup(int nDigitalPin);

  private:
    int nPin;

};
