#include <Ardumote.h>
 
class ArdumoteMD5: public Ardumote {
  public:
    void setup(long nControllerID, char* secret);
  protected:
    char* getHash(char* strToHash);

};
