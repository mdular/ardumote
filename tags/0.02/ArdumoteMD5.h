/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include <Ardumote.h>
 
class ArdumoteMD5: public Ardumote {
  public:
    void setup(long nControllerID, char* secret, int TXLED, int RXLED);
  protected:
    char* getHash(char* strToHash);

};
