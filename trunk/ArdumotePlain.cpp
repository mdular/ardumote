#include "ArdumotePlain.h"

void ArdumotePlain::setup(long nControllerID, char* secret, int TXLED, int RXLED) {
  Ardumote::setup(nControllerID, secret, TXLED, RXLED);
  nProtocolVersion = 1;
}

char* ArdumotePlain::getHash(char* strToHash) {
  return sSecret;
}

