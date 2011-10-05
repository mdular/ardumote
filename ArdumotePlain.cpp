#include "ArdumotePlain.h"

void ArdumotePlain::setup(long nControllerID, char* secret) {
  Ardumote::setup(nControllerID, secret);
  nProtocolVersion = 1;
}

char* ArdumotePlain::getHash(char* strToHash) {
  return sSecret;
}

