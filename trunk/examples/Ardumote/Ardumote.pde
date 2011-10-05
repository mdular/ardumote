// ==== General Includes =========
#include <Ardumote.h>
#include <SPI.h>
#include <Ethernet.h>
#include <RCSwitch.h>
#include <Time.h>
#include <ArdumotePlain.h>
// ===== Maintenance Modules =====
#include <SensorMaintenance.h>
#include <ActorMaintenance.h>
// ===== Com Modules =============
#include <ComSerial.h>
#include <ComEthernetIRC.h>
#include <ComEthernetHTTP.h>
// ===== Sensor Modules ==========
#include <SensorAnalog.h>
#include <SensorDigital.h>
// ===== Actor Modules ===========
#include <ActorAnalog.h>
#include <ActorDigital.h>
#include <ActorRCSwitch.h>
// ===============================


byte mac[]     = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[]      = { 192,168,0,11 };

SensorMaintenance s0;
ActorMaintenance  a0;

ComSerial         c1;
ComEthernetIRC    c2;

SensorAnalog      s1;

ActorAnalog       a1;
ActorAnalog       a2;
ActorDigital      a3;

ArdumotePlain myArdumote;

void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("setup start.");
  Ethernet.begin(mac, ip);

  myArdumote.setup(5, "5a7fa4a21d4ebfd543c9133cd28e5278");

  // === Maintenance Modules ===
  s0.setup();
  myArdumote.addSensorModule( &s0 );
  a0.setup();
  myArdumote.addActorModule( &a0 );  

  // === ComModules ===
  //myArdumote.addComModule(&c1);
  
  c2.setup();
  myArdumote.addComModule(&c2);
 
  // === Sensors ===
  s1.setup(A1, 10);
  myArdumote.addSensorModule( &s1 );

  // === Actors ===
  a1.setup(5);
  myArdumote.addActorModule( &a1 );

  a2.setup(6);
  myArdumote.addActorModule( &a2 );

  a3.setup(7);
  myArdumote.addActorModule( &a3 );

  Serial.println("setup done");
}

void loop() {
  myArdumote.loop();
}

