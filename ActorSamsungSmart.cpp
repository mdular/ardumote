/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT
*/

#include "Arduino.h"
#include "ActorSamsungSmart.h"

EthernetClient client;

void ActorSamsungSmart::setup(char* sName, byte myMac[6], byte remoteIp[4]) {
  setName(sName);
  nDeviceTypeID = 24;
  
  ip[0] = remoteIp[0];
  ip[1] = remoteIp[1];
  ip[2] = remoteIp[2];
  ip[3] = remoteIp[3];  

  mac[0] = myMac[0];
  mac[1] = myMac[1];
  mac[2] = myMac[2];
  mac[3] = myMac[3];  
  mac[4] = myMac[4];  
  mac[5] = myMac[5];  

}

bool ActorSamsungSmart::exec(char* p) {
  if (client.connect(yserver, 6667)) {

  }
}

void ActorSamsungSmart::sendString(char* s) {
    if (client.connected()) {
        client.write( strlen(s) );
        client.write( 0 );
        client.print( s );
    }
}

void ActorSamsungSmart::sendInit() {
    if (client.connected()) {
    client.write(0);
    client.print('foo');
    sendString( 
    $part1 =   chr(0x00) . generateString('foo') . generateString( chr(0x64) . chr(0x00) . generateString('MTI3LjAuMC4x') . generateString( base64_encode($mac) ) . generateString('QXJkdW1vdGU=') ) 
			 . chr(0x00) . generateString('foo') . generateString( chr(0xc8) . chr(0x00) );
    }
}