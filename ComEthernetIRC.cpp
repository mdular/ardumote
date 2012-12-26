/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "ComEthernetIRC.h"
#include "Arduino.h"

char yserver[] = "irc.ardumote.com";
EthernetClient client;// ( yserver, 6667);

ComEthernetIRC::ComEthernetIRC() {

}

void ComEthernetIRC::setup(int nLedPin) {
  pinMode(nLedPin, OUTPUT);
  nStatusLEDPin = nLedPin;
  connect();
}

void ComEthernetIRC::clearVars() {
  nInBufferPos = 0;
  sInBuffer[0] = '\0';
  bAvailable = false; 
  bReady = false;
}

void ComEthernetIRC::connect() {
  clearVars();
  for (int i = 0; i<10; i++) {
    randomSeed(analogRead(A0)+analogRead(A1)+analogRead(A2)+analogRead(A3)+analogRead(A4)+analogRead(A5));
    myNick[i] = (char)random(65,90);
  }
  myNick[10] = '\0';

    
  if (client.connect(yserver, 6667)) {
    client.print("NICK ");
    client.print(myNick);
    client.println();
    client.print("USER ardumote");
    client.print("1");
    client.println(" 8 * : arduino");
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
          if (strstr(sInBuffer, "376") != NULL) {
            sInBuffer[0] = 'c'; sInBuffer[1] = 'o'; sInBuffer[2] = 'n'; sInBuffer[3] = '\0'; 
            setStatus(true);
            sReturnCommand = "con";
            bAvailable = true;
            return true;
          }
          processIRCstr();
          return bAvailable;
        } else if (c!='\r') {
          sInBuffer[nInBufferPos++] = c;
        }
      }
      if (nInBufferPos > 200) {
        clearVars();
      }      
    } else {
      setStatus(false);
      client.stop();
      delay(5000);
      connect();
    }
    return false;
}

void ComEthernetIRC::processIRCstr() {
  // PING/PONG
  if (sInBuffer[0] == 'P' && sInBuffer[1] == 'I' && sInBuffer[2] == 'N' && sInBuffer[3] == 'G') {
    sInBuffer[1] = 'O';
    client.println(sInBuffer);
    clearVars();
    return;
  }

  sReturnCommand = strstr (sInBuffer, "PRIVMSG");
  if (sReturnCommand != NULL)  {
    sReturnCommand = strstr( sReturnCommand, myNick);
    if (sReturnCommand != NULL) {
      sReturnCommand = strstr( sReturnCommand, ":")+1;
      if (sReturnCommand != NULL) {
        bAvailable = true;
        return;
      }
    }
  }
  clearVars();  
}

char* ComEthernetIRC::read() {
  clearVars();
  return sReturnCommand;
}

bool ComEthernetIRC::send(char* sCommand) {
    if (client.connected()) {
      client.print("PRIVMSG ardumote :");
      client.println(sCommand);

    } else {
      setStatus(false);
      client.stop();
      delay(5000);
      connect();
    }
}

void ComEthernetIRC::setStatus(bool status) {
  if (status) {
    digitalWrite(nStatusLEDPin, HIGH);
  } else {
    digitalWrite(nStatusLEDPin, LOW);
  }
  bReady = status;
}