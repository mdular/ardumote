#include "ComEthernetIRC.h"
#include "WProgram.h"

byte yserver[] = { 78,47,112,60};
Client client ( yserver, 6667);

ComEthernetIRC::ComEthernetIRC() {
  
}

void ComEthernetIRC::setup() {
  nCommandBufferPos = 0;
  bAvailable = false;
  sReturnCommand[0] = '\0';
  this->connect();  
}

void ComEthernetIRC::connect() {
  for (int i = 0; i<10; i++) {
    randomSeed(analogRead(0));
    myNick[i] = (char)random(65,90);
  }
  myNick[10] = '\0';
    
  if (client.connect()) {
    
    client.print("NICK ");
    client.print(myNick);
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
        if (c == '\n') {
          sReturnCommand[nCommandBufferPos] = '\0';
          Serial.println(sReturnCommand);
          processIRCstr();
          return bAvailable;
        } else if (c!='\r') {
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

void ComEthernetIRC::processIRCstr() {
  char* pch;
  char* msg;
  pch = strtok (sReturnCommand, ":");
  while (pch != NULL) {
    if (strcmp(pch, "PING") == 0) {
      client.println("PONG");
      return;
    }

    msg = pch;
    pch = strtok (NULL, " ");
  }
  
  pch = strtok (sReturnCommand, " ");
  while (pch != NULL) {
    if (strcmp(pch, "PRIVMSG") == 0) {
    Serial.print("sl:");
      Serial.println(strlen(msg));
      for (int i = 0; i < strlen(msg); i++) {
        sReturnCommand[i] = msg[i];
      }
      sReturnCommand[strlen(msg)] = '\0';
      bAvailable = true;
      
      return;
    }
    pch = strtok (NULL, " ");
  }
  
  bAvailable = false;
}

char* ComEthernetIRC::read() {
  nCommandBufferPos = 0;
  bAvailable = false;
  return sReturnCommand;
}

bool ComEthernetIRC::send(char* sCommand) {
    if (client.connected()) {
      client.print("PRIVMSG ardumote :");
      client.println(sCommand);
    } else {
      client.stop();
      delay(5000);
      connect();
    }
}