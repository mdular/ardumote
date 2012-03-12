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
#include <SensorRCSwitch.h>
// ===== Actor Modules ===========
#include <ActorAnalog.h>
#include <ActorDigital.h>
#include <ActorRCSwitch.h>
// ===============================


#define ARDUMOTE_CONTROLLER_ID 33
#define ARDUMOTE_SHARED_SECRET "efaa83d0d1f5456ee9fe99a8953fe653"

byte mac[]     = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {

  Serial.begin(9600);
  Ethernet.begin(mac);
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
    ComSerial c1;  
    myArdumote.addComModule(&c1);

//    ComEthernetIRC c2;  
//    c2.setup(13);                          // LED on pin 13 indicates Connection Status
//    myArdumote.addComModule(&c2);
  // ====== /ComModules ================================================================================

  // ===== Sensors =====================================================================================
    SensorRCSwitch s1;
    s1.setup("RCSwitch R.", 0);         // LDR connected to analog pin 0 polling value every 10 seconds
    myArdumote.addSensorModule( &s1 );

    SensorAnalog s2;
    s2.setup("Analog", A0, 5);         // LDR connected to analog pin 0 polling value every 10 seconds
    myArdumote.addSensorModule( &s2 );
  // ===== /Sensors ===================================================================================

  // ==== Actors ======================================================================================
    ActorRCSwitch a1;
    a1.setup("RCSwitch S.", 10);           // A LED connected to pin 5
    myArdumote.addActorModule( &a1 );
  // ==== /Actors =====================================================================================

  
  Serial.println("setup done");
  
  while (true) {
    myArdumote.loop();    
  }
  
}

void loop() {
}