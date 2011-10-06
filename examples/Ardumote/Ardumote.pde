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


#define ARDUMOTE_CONTROLLER_ID 5
#define ARDUMOTE_SHARED_SECRET "5a7fa4a21d4ebfd543c9133cd28e5278"
byte mac[]     = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[]      = { 192,168,0,11 };


void setup() {

  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  delay(1000);

  // ======= Ardumote =================================================================================

    ArdumotePlain myArdumote;
    myArdumote.setup(ARDUMOTE_CONTROLLER_ID, ARDUMOTE_SHARED_SECRET);

  // ======= /Ardumote ================================================================================

  // ======= Maintenance Modules ======================================================================

    SensorMaintenance s0;  s0.setup();  myArdumote.addSensorModule( &s0 );
    ActorMaintenance  a0;  a0.setup();  myArdumote.addActorModule( &a0 );  

  // ======= /Maintenance Modules ======================================================================

  // ====== ComModules =================================================================================

    // ComSerial c1;
    // c1.setup();
    // myArdumote.addComModule(&c1);
      
    ComEthernetIRC c2;  
    c2.setup(13);                          // LED on pin 13 indicates Connection Status
    myArdumote.addComModule(&c2);

  // ====== /ComModules ================================================================================

  // ===== Sensors =====================================================================================

    SensorAnalog s1;
    s1.setup("LDR Light", A0, 10);         // LDR connected to analog pin 0 polling value every 10 seconds
    myArdumote.addSensorModule( &s1 );
  
    SensorAnalog s2;
    s2.setup("LM35 Temperature", A1, 10);  // LM35 temperature sensor connected to analog pin 1
    myArdumote.addSensorModule( &s2 );

  // ===== /Sensors ===================================================================================

  // ==== Actors ======================================================================================

    ActorAnalog a1;
    a1.setup("LED PWM Blue", 5);           // A blue LED connected to pin 5
    myArdumote.addActorModule( &a1 );
  
    ActorDigital a2;
    a2.setup("LED Digital Red", 6);        // A red LED connected to pin 6
    myArdumote.addActorModule( &a2 );
  
    ActorRCSwitch a3;
    a3.setup("RCSwitch", 7);               // A 433MHz transmitter connected to pin 7
    myArdumote.addActorModule( &a3 );

  // ==== /Actors =====================================================================================

  
  Serial.println("setup done");
  
  while (true) {
    myArdumote.loop();    
  }
  
}

void loop() {
}

