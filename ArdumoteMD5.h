#include <Ardumote.h>
 
class ArdumoteMD5: public Ardumote {
  public:
    void setup(long nControllerID, char* secret, int TXLED, int RXLED);
  protected:
    char* getHash(char* strToHash);

};
