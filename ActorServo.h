#include <ActorModule.h>
#include <Servo.h> 

class ActorServo : public ActorModule {
  
  public:
    bool exec(char* p1);
    void setup(char* sName, int nDigitalPin);

  private:
    int nPin;
	Servo myservo;

};
