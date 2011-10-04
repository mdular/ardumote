#include "ComEthernetIRC.h"
#include "WProgram.h"

byte yserver[] = { 78,47,112,60};
Client client ( yserver, 6667);

ComEthernetIRC::ComEthernetIRC() {

}

void ComEthernetIRC::setup() {
  connect();
}

void ComEthernetIRC::clearVars() {
  nInBufferPos = 0;
  sInBuffer[0] = '\0';
  bAvailable = false; 
}

void ComEthernetIRC::connect() {
  clearVars();
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
          sInBuffer[nInBufferPos] = '\0';
          processIRCstr();
          return bAvailable;
        } else if (c!='\r') {
          sInBuffer[nInBufferPos++] = c;
        }
      }
      if (nInBufferPos > 201) {
        clearVars();
      }      
    } else {
      client.stop();
      delay(5000);
      connect();
    }
    return false;
}

void ComEthernetIRC::processIRCstr() {
  if (sInBuffer[0] == 'P' && sInBuffer[1] == 'I' && sInBuffer[2] == 'N' && sInBuffer[3] == 'G') {
    sInBuffer[1] = 'O';
    client.println(sInBuffer);
    clearVars();
    Serial.println("PONG");
    return;
  }
  Serial.println(sInBuffer);

  sReturnCommand = strstr (sInBuffer, "PRIVMSG");
  if (sReturnCommand != NULL)  {
    sReturnCommand = strstr( sReturnCommand, myNick);
    if (sReturnCommand != NULL) {
      sReturnCommand = strstr( sReturnCommand, ":")+1;
      if (sReturnCommand != NULL) {
        bAvailable = true;
      }
    }
  }
}

char* ComEthernetIRC::read() {
  clearVars();
  return sReturnCommand;
}

bool ComEthernetIRC::send(char* sCommand) {
    if (client.connected()) {
      client.print("PRIVMSG ardumote :");
      client.println(sCommand);
      client.print("PRIVMSG #test :");
      client.println(sCommand);
    } else {
      client.stop();
      delay(5000);
      connect();
    }
}