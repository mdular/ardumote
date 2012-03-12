#include <ActorModule.h>
#include <Servo.h> 

class ActorServo : public ActorModule {
  
  public:
    bool exec(long p1, long p2, long p3);
    void setup(char* sName, int nDigitalPin);

  private:
    int nPin;
	Servo myservo;

};
