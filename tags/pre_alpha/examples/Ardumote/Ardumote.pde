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


#define ARDUMOTE_CONTROLLER_ID 11
#define ARDUMOTE_SHARED_SECRET "2d520b8f5ea2cf6113a578f57b45201c"

byte mac[]     = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[]      = { 192,168,0,11 };


void setup() {

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  delay(1000);

  Serial.println("setup start");

  // ======= Ardumote =================================================================================
    Serial.println("Setup Ardumote");
    ArdumotePlain myArdumote;
    myArdumote.setup(ARDUMOTE_CONTROLLER_ID, ARDUMOTE_SHARED_SECRET);
  // ======= /Ardumote ================================================================================

  // ======= Maintenance Modules ======================================================================
    Serial.println("Setup Maintenance Modules");
    SensorMaintenance s0;  s0.setup();  myArdumote.addSensorModule( &s0 );
    ActorMaintenance  a0;  a0.setup();  myArdumote.addActorModule( &a0 );  
  // ======= /Maintenance Modules ======================================================================

  // ====== ComModules =================================================================================
    ComEthernetIRC c2;  
    c2.setup(13);                          // LED on pin 13 indicates Connection Status
    myArdumote.addComModule(&c2);
  // ====== /ComModules ================================================================================

  // ===== Sensors =====================================================================================
    SensorAnalog s1;
    s1.setup("myLDR", A0, 10);         // LDR connected to analog pin 0 polling value every 10 seconds
    myArdumote.addSensorModule( &s1 );
  // ===== /Sensors ===================================================================================

  // ==== Actors ======================================================================================
    ActorAnalog a1;
    a1.setup("myLED PWM", 5);           // A LED connected to pin 5
    myArdumote.addActorModule( &a1 );

    ActorDigital a2;
    a2.setup("myLED", 6);           // A LED connected to pin 6
    myArdumote.addActorModule( &a2 );
  // ==== /Actors =====================================================================================

  
  Serial.println("setup done");
  
  while (true) {
    myArdumote.loop();    
  }
  
}

void loop() {
}

