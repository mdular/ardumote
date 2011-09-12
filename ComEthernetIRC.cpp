#include "ComEthernetIRC.h"

byte yserver[] = { 78,47,112,60,1};
Client client ( yserver, 6667);

ComEthernetIRC::ComEthernetIRC() {
  
}

void ComEthernetIRC::setup(byte mac[6], byte ip[4], byte remoteIp[4]) {
  Ethernet.begin(mac, ip);

  
  
  nReturnCommandPos = 0;
  bAvailable = false;
  delay(1000);
  connect();
}

void ComEthernetIRC::connect() {
  if (client.connect()) {
    Serial.println("connected");
    client.println("NICK sui82");
    client.println("USER sui77 8 * : Suat Oezguer");
    client.println("JOIN #test");
  } else {
    
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
          sReturnCommand[nReturnCommandPos] = '\0';
          bAvailable = true;
          return true;
        } else {
          sReturnCommand[nReturnCommandPos++] = c;
        }
      }
    } else {
      client.stop();
      delay(5000);
      connect();
    }
    return false;
}

char* ComEthernetIRC::read() {
  nReturnCommandPos = 0;
  bAvailable = false;
  return sReturnCommand;
}

bool ComEthernetIRC::send(char* sCommand) {
    if (client.connected()) {
      client.print("PRIVMSG sui :");
      client.println(sCommand);
    } else {
      client.stop();
      delay(5000);
      connect();
    }
}