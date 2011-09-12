#include "ComEthernetHTTP.h"

Server xserver(80);

ComEthernetHTTP::ComEthernetHTTP() {
  
}

void ComEthernetHTTP::setup(byte mac[6], byte ip[4], byte remoteIp[4]) {
  Ethernet.begin(mac, ip);
  serverIP[0] = remoteIp[0];
  serverIP[1] = remoteIp[1];
  serverIP[2] = remoteIp[2];
  serverIP[3] = remoteIp[3];
}

bool ComEthernetHTTP::available() {
  Client client = xserver.available();
  if (client) {
    int nCommandPos=-1;
    sReturnCommand[0] = '\0';
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/plain");
          client.println();
          client.println("ok");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
        if (nCommandPos>-1) {
          sReturnCommand[nCommandPos++] = c;
        }
        if (c == '?' && nCommandPos == -1) {
          nCommandPos = 0;
        }
      }
    }
    if (nCommandPos!=-1) {
      sReturnCommand[nCommandPos] = '\0';
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }

}

char* ComEthernetHTTP::read() {
return "aaa";
}

bool ComEthernetHTTP::send(char* sCommand) {
  Client client(serverIP, 80);
  if (client.connect()) {
    client.print("GET /input.php?d=");
    client.print( sCommand );
    client.println(" HTTP/1.0");
    client.println("Host: ardumote.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
      }
    }
   
    client.stop();

    return true;
    
  } else {
    return false;
  }

}