#include "ArdumoteMD5.h"
#include "MD5.c"

void ArdumoteMD5::setup(long nControllerID, char* secret, int TXLED, int RXLED) {
  Ardumote::setup(nControllerID, secret, TXLED, RXLED);
  nProtocolVersion = 2;
}

char* ArdumoteMD5::getHash(char* strToHash) {
Serial.print("sth:");
Serial.println(strToHash);
  unsigned char strToHashU[233];
  char* sReturnValue;
  
  int i = 0;
  for (int j = 0; j<strlen(strToHash) && j<200; j++) {
    strToHashU[i++] = strToHash[j];
  }
  for (int j = 0; j<strlen(sSecret); j++) {
    strToHashU[i++] = sSecret[j];
  }
  strToHashU[i] = '\0';
  
  sReturnValue = MD5(strToHashU, strlen(strToHash)+strlen(sSecret));
  return sReturnValue;
}

