#include <RCSwitch.h>
#include <MD5.c>

#include <Ardumote.h>

// ===== Com Modules =====
#include <ComSerial.h>
#include <ComEthernetIRC.h>
#include <ComEthernetHTTP.h>

// ===== Sensor Modules =====
#include <SensorAnalog.h>
#include <SensorDigital.h>

// ===== Actor Modules =====
#include <ActorAnalog.h>
#include <ActorDigital.h>
#include <ActorRCSwitch.h>


// Other stuff
#include <SPI.h>
#include <Ethernet.h>


//#define ARDUMOTE_CONTROLLER_ID 1



byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,178,5 };
byte server[] = { 192, 168, 1, 5 };


ComModule*    ComModules[5];
ActorModule*  Actors[10];
SensorModule* Sensors[10];

int numComModules = 0;
int numActors = 0;
int numSensors = 0;

ComSerial c1 = ComSerial();

SensorDigital s1 = SensorDigital();
SensorAnalog s2 = SensorAnalog();

ActorDigital a1 = ActorDigital();  
ActorAnalog a2 = ActorAnalog();  
ActorRCSwitch a3 = ActorRCSwitch();


void setup() {
  Serial.begin(9600);
  Serial.print("setup start.");
  // ComModules

  ComModules[numComModules++] = &c1;
  /*
    ComEthernetIRC c2 = ComEthernetIRC();
    ComModules[numComModules++] = &c1;
    ComEthernetHTTP c3 = ComEthernetHTTP();
    ComModules[numComModules++] = &c3;
  */
 
  // Sensors
  s1.setInterval(5);
  s1.setup(7);
  Sensors[numSensors++] = &s1;

  s2.setInterval(20);
  s1.setup(A0);
  Sensors[numSensors++] = &s2;
  
  // Actors
  a1.setup(13);
  Actors[numActors++] = &a1;

  a2.setup(5);
  Actors[numActors++] = &a2;

  a3.setup(7);
  Actors[numActors++] = &a3;

  Serial.println("setup done");
}

void loop() {
  // Com
  for (int i = 0; i<numComModules; i++) {
    if (ComModules[i]->available() ) {
      char* command = ComModules[i]->read();
      processCommand( command );

      Serial.print("Command (Mod #");
      Serial.print(0);
      Serial.print("): ");
      Serial.println( command );
    }
  }

  // Sensor
  for (int i = 0; i<numSensors; i++) {
    if (Sensors[i]->available()) {
      int nV = Sensors[i]->getValue();
      sendToComModules( nV );
    }
  }
}


void sendToComModules(long nV) {
  for (int i = 0; i<numComModules; i++) {
    char* v = "123456789012345"; 
    ltoa(nV, v, 10);
    ComModules[i]->send(v);
  }
}

char* long2string(long l) {
  char* r[13];
  
}

void log(char* msg) {
  Serial.println(msg);
}

void processCommand(char* s) {
  printAvailableMemory();

  char* md5calculated;
  char md5[33];
  int len = strlen(s);
  
  if (s[0] != '1' || s[1] != '*') {
    log("unsupported protocol version");
    return;
  }
  
  if (len < 34) {
    log("message too short");
    return;
  }
  
  int j=0;
  for (int i = len-32; i<len; i++) {
    md5[j++] = s[i];
  }
  md5[j] = '\0';
  
  unsigned char strToHash[201];
  for (int i = 0; i<len-32; i++) {
    strToHash[i] = s[i];
    strToHash[i+1]='\0';
  }

  md5calculated = MD5(strToHash, len-32);
  if (strcmp(md5calculated, md5) != 0) {
    log("invalid md5");
    Serial.print("Expected: ");
    Serial.println(md5calculated);
//    return;
  }
  
  
/*
  if (strcmp(s, "on") == 0) {
    Serial.println("exec");
    Actors[2]->exec(5471 );
  } else {
    Actors[2]->exec(5396 );    
  }
  */
}


int printAvailableMemory() {
  int size = 2048; // Use 2048 with ATmega328
  byte *buf;

  while ((buf = (byte *) malloc(--size)) == NULL)
    ;

  free(buf);
  Serial.print("Memory: ");
  Serial.println(size);
}

