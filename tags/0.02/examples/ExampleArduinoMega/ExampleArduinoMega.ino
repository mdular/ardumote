/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT

    Ardumote example sketch for Mega boards

    Pin   Device
    2     433Mhz AM Receiver
    4     Servo Motor
    5     Servo Motor
    42    Status LED (Recieve)
    44    Status LED (Transmit)
    46    Status LED (IRC Connection)
    A1    433Mhz AM Transmitter
    A10   Analog temperature sensor
*/
// ==== Basic configuration =====================================

#define ARDUMOTE_CONTROLLER_ID 123
#define ARDUMOTE_SHARED_SECRET "01234567890abcdef01234567890abcd"

#define STATUS_LED_RX  42
#define STATUS_LED_TX  44
#define STATUS_LED_IRC 46

byte mac[]     = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// ==== General Includes ========================================
#include <Ardumote.h>
#include <SPI.h>
#include <Ethernet.h>
#include <RCSwitch.h>
#include <Servo.h>
#include <Time.h>
#include <ArdumotePlain.h>
#include <ArdumoteMD5.h>
// ===== Maintenance Modules ====================================
#include <SensorMaintenance.h>
#include <ActorMaintenance.h>
// ===== Com Modules ============================================
#include <ComSerial.h>
#include <ComEthernetIRC.h>
#include <ComEthernetHTTP.h>
// ===== Sensor Modules =========================================
#include <SensorAnalog.h>
#include <SensorDigital.h>
#include <SensorRCSwitch.h>
// ===== Actor Modules ==========================================
#include <ActorAnalog.h>
#include <ActorDigital.h>
#include <ActorRCSwitch.h>
#include <ActorServo.h>
// ==============================================================

void setup() {

  // Init ethernet
  Ethernet.begin(mac);
  delay(1000);

  // Init ardumote itself
  ArdumoteMD5 myArdumote;
  myArdumote.setup(ARDUMOTE_CONTROLLER_ID, ARDUMOTE_SHARED_SECRET, STATUS_LED_TX, STATUS_LED_RX);

  // Init maintenance modules (Do not remove)
  SensorMaintenance s0;
  s0.setup();  
  myArdumote.addSensorModule( &s0 );
  
  ActorMaintenance  a0;  
  a0.setup();  
  myArdumote.addActorModule( &a0 );  

  // Init ComModules
  ComEthernetIRC c2;
  c2.setup(STATUS_LED_IRC);
  myArdumote.addComModule(&c2);

  // Init sensors
  SensorRCSwitch s1;
  s1.setup("433Mhz RX", 0); // 433Mhz AM Receiver at Pin 2
  myArdumote.addSensorModule( &s1 );

  SensorAnalog s2;
  s2.setup("Temperature", A10, 60); // LM35 Temp. Sensor at Pin A10
  myArdumote.addSensorModule( &s2 );

  // Init actors
  ActorRCSwitch a1;
  a1.setup("433Mhz TX", A1); // 433Mhz AM Transmitter at Pin A1
  myArdumote.addActorModule( &a1 );
  
  ActorServo a2;
  a2.setup("Servo 1", 5); // Servo motor at Pin 5
  myArdumote.addActorModule( &a2 );

  ActorServo a3;
  a3.setup("Servo 2", 4); // Servo motor at Pin 4
  myArdumote.addActorModule( &a3 );
  
  // run
  while (true) {
    myArdumote.loop();    
  }

}

void loop() {
}
