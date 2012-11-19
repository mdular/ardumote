/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include "ActorSamsungSmart.h"

void ActorSamsungSmart::setup(char* sName, IPAddress server) {
  setName(sName);
  nDeviceTypeID = 24;
  srv=server; 
}

bool ActorSamsungSmart::exec(char* cmd) {
  EthernetClient client;
  if (client.connect(srv, 55000)) {
    uint8_t part1[] = {0,1,0,102,56,0,100,0,12,0,77,84,73,51,76,106,65,117,77,67,52,120,24,0,77,71,85,116,77,71,77,116,77,106,107,116,77,50,85,116,89,106,69,116,78,71,89,61,12,0,81,88,74,107,100,87,49,118,100,71,85,61,0,1,0,102,2,0,200,0,0,1,0,102,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char text[100];    
    base64_encode(text,cmd,strlen(cmd));
    part1[74+0] = 5+strlen(text);
    part1[74+5] = strlen(text);
    for (int i = 0; i<strlen(text); i++) {
      part1[74+7+i] = text[i];
    }
    client.write(part1,74+7+strlen(text));
    client.stop();
  } 
}

