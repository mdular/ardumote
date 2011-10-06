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
SensorAnalog      s2;


ActorAnalog       a1;
ActorDigital      a2;
ActorRCSwitch     a3;

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
  c1.setup();
  myArdumote.addComModule(&c1);
  
  c2.setup(13);        // LED on Pin 13 indicates Connection Status
  myArdumote.addComModule(&c2);
 
  // === Sensors ===
  s1.setup("LDR Light", A0, 600);
  myArdumote.addSensorModule( &s1 );

  s2.setup("LM35 Temperature", A1, 600);
  myArdumote.addSensorModule( &s2 );
  
  // === Actors ===
  a2.setup("LED Digital Red", 6);
  myArdumote.addActorModule( &a2 );

  a3.setup("RCSwitch", 7);
  myArdumote.addActorModule( &a3 );

  a1.setup("LED PWM Blue", 5);
  myArdumote.addActorModule( &a1 );
  
  Serial.println("setup done");
}

void loop() {
  myArdumote.loop();
}

