
// ==== General Includes ====
#include <SPI.h>
#include <Ethernet.h>
#include <RCSwitch.h>
//#include <Time.h>
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





byte mac[]     = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[]      = { 192,168,0,5 };


ComSerial      c1 = ComSerial();
ComEthernetIRC c2 = ComEthernetIRC();

//SensorDigital  s1 = SensorDigital();
SensorAnalog   s2 = SensorAnalog();

ActorDigital   a1 = ActorDigital();  
/*
ActorAnalog    a2 = ActorAnalog();  
ActorRCSwitch  a3 = ActorRCSwitch();
*/
Ardumote myArdumote = Ardumote( );

void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("setup start.");

  Ethernet.begin(mac, ip);
 
  // === Time ===
//  setSyncProvider(timeSync);

  myArdumote.setup(4, "a603a3c9aef87d0ccc5732385c08d692");

  // === ComModules ===
  myArdumote.addComModule(&c1);
  
  c2.setup();  
  myArdumote.addComModule(&c2);
 
  // === Sensors ===
  s2.setInterval(5);
  s2.setup(A1);
  myArdumote.addSensorModule( &s2);
/*
  s2.setInterval(20);
  s1.setup(A0);
  myArdumote.addSensorModule( &s2);
  
  // === Actors ===
  a1.setup(13);
  myArdumote.addActorModule( &a1);

  a2.setup(5);
  myArdumote.addActorModule( &a2);

  a3.setup(7);
  myArdumote.addActorModule( &a3);
*/
  Serial.println("setup done");
}

void loop() {
  myArdumote.loop();
}



/*
void processCommand(char* s) {
  printAvailableMemory();

  char* md5calculated;
  char md5[33];
  int len = strlen(s);
  
  if (s[0] != '1' || s[1] != '*') {
    //log("unsupported protocol version");
    return;
  }
  
  if (len < 34) {
    //log("message too short");
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
    //log("invalid md5");
    Serial.print("Expected: ");
    Serial.println(md5calculated);
//    return;
  }
  
  

  if (strcmp(s, "on") == 0) {
    Serial.println("exec");
    Actors[2]->exec(5471 );
  } else {
    Actors[2]->exec(5396 );    
  }
  
}
*/

void printAvailableMemory() {
  int size = 2048; // Use 2048 with ATmega328
  byte *buf;

  while ((buf = (byte *) malloc(--size)) == NULL)
    ;

  free(buf);
  Serial.print("Memory: ");
  Serial.println(size);
}


/*time_t timeSync() {
  return 0;
}*/
