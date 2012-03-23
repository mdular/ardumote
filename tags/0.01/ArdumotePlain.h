#include <Ardumote.h>
 
class ArdumotePlain: public Ardumote {
  public:
    void setup(long nControllerID, char* secret);
  protected:
    char* getHash(char* strToHash);

};
