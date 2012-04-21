#include <ActorModule.h>

class ActorAnalog3 : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, int nAnalogPin1, int nAnalogPin2, int nAnalogPin3);

  private:
    int nPin1;
    int nPin2;
    int nPin3;
    

};
