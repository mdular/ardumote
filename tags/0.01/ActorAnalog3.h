#include <ActorModule.h>

class ActorAnalog3 : public ActorModule {
  
  public:
    bool exec(long p1, long p2, long p3);
    void setup(char* sName, int nAnalogPin1, int nAnalogPin2, int nAnalogPin3);

  private:
    int nPin1;
    int nPin2;
    int nPin3;
    

};
