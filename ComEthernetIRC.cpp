#include "ComEthernetIRC.h"
#include "WProgram.h"

byte yserver[] = { 78,47,112,60};
Client client ( yserver, 6667);

ComEthernetIRC::ComEthernetIRC() {
  
}

void ComEthernetIRC::setup(byte mac[6], byte ip[4], byte remoteIp[4]) {
  nCommandBufferPos = 0;
  bAvailable = false;
  this->connect();
  sReturnCommand[0] = '\0';
}

void ComEthernetIRC::connect() {
  if (client.connect()) {
    
    client.print("NICK ");
    for (int i = 0; i<10; i++) {
      randomSeed(analogRead(0));
      client.print((char)random(65,90));
    }
    client.println();
    
    client.print("USER ardumote");
    client.print("1");
    client.println(" 8 * : Suat Oezguer");
    client.println("JOIN #test");
  } 
}

bool ComEthernetIRC::available() {
    if (bAvailable) {
      return true;
    }
    if (client.connected()) {
      if (client.available()) {
        char c = client.read();
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
    } else {
      nCommandBufferPos = 0;
      client.stop();
      delay(5000);
      connect();
    }
    return false;
}

char* ComEthernetIRC::read() {
  nCommandBufferPos = 0;
  bAvailable = false;
  return sReturnCommand;
}

bool ComEthernetIRC::send(char* sCommand) {
    if (client.connected()) {
      client.print("PRIVMSG sui__ :");
      client.println(sCommand);
    } else {
      client.stop();
      delay(5000);
      connect();
    }
}