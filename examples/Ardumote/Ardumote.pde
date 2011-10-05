
// ==== General Includes ====
#include <SPI.h>
#include <Ethernet.h>
#include <RCSwitch.h>
#include <Time.h>
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


//ComSerial      c1 = ComSerial();
ComEthernetIRC c2 = ComEthernetIRC();

SensorAnalog   s1 = SensorAnalog();

ActorDigital   a1 = ActorDigital();  
ActorAnalog    a2 = ActorAnalog();  
ActorRCSwitch  a3 = ActorRCSwitch();

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
//  myArdumote.addComModule(&c1);
  
  c2.setup();  
  myArdumote.addComModule(&c2);
 
  // === Sensors ===
  s1.setInterval(30);
  s1.setup(A1);
  myArdumote.addSensorModule( &s1);

  // === Actors ===
  a1.setup(7);
  myArdumote.addActorModule( &a1);
/*
  a2.setup(5);
  myArdumote.addActorModule( &a2);
*/
  a3.setup(6);
  myArdumote.addActorModule( &a3);

  Serial.println("setup done");
}

void loop() {
  myArdumote.loop();
}




/*time_t timeSync() {
  return 0;
}*/