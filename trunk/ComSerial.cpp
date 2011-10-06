#include "ComSerial.h"

ComSerial::ComSerial() {
   bAvailable = false;
   nCommandBufferPos = 0;
   sReturnCommand[0] = '\0';
}

void ComSerial::setup() {
}

bool ComSerial::available() {
    if (bAvailable) {
      return true;
    }
	if (Serial.available()) {
		char c = Serial.read();
		if (c == 13) {
			sReturnCommand[nCommandBufferPos] = '\0';
			bAvailable = true;
			return true;
		} else {
			sReturnCommand[nCommandBufferPos++] = c;
		}
	}
	if (nCommandBufferPos > 190) {
		nCommandBufferPos = 0;
	}
	return false;
}

char* ComSerial::read() {
  nCommandBufferPos = 0;
  bAvailable = false;
  return sReturnCommand;
}


bool ComSerial::send(char* sCommand) {
  Serial.println(sCommand);
}