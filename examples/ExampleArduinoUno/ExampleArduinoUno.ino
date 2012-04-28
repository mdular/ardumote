/*
    http://www.ardumote.com
    Copyright (c) 2012 Suat Özgür
    http://opensource.org/licenses/MIT

    Ardumote example sketch for Duemilanove/Uno boards

    The difference to Mega boards is due to memory limitation. The
    authentication is done in plaintext and thus less secure 
    (vulnerable to man in the middle attacks). Also you can not use 
    the RCSwitch library. So this example is limited to a couple
    of LEDs and a analog sensor.

    Pin   Device
    3     Status LED (Recieve)
    4     Status LED (Transmit)
    5     Status LED (IRC Connection)
    6     LED (PWM)
    A0    Analog sensor (LM35 for example)
    A1    LED
    A2    LED
    A3    LED
*/
// ==== Basic configuration =====================================

#define ARDUMOTE_CONTROLLER_ID 123
#define ARDUMOTE_SHARED_SECRET "01234567890abcdef01234567890abcd"

#define STATUS_LED_RX  3
#define STATUS_LED_TX  4
#define STATUS_LED_IRC 5 

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
  ArdumotePlain myArdumote;
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
  SensorAnalog s1;
  s1.setup("Analog Sensor / Pin A0", A0, 360);

  // Init actors
  ActorDigital a1;
  a1.setup("LED / Pin A1", A1);
  myArdumote.addActorModule(&a1);
  
  ActorDigital a2;
  a2.setup("LED / Pin A2", A2);
  myArdumote.addActorModule(&a2);

  ActorDigital a3;
  a3.setup("LED / Pin A3", A3);
  myArdumote.addActorModule(&a3);

  ActorAnalog a4;
  a4.setup("PWM LED / Pin 6", 6);
  myArdumote.addActorModule(&a4);
  
  // run
  while (true) {
    myArdumote.loop();    
  }

}

void loop() {
}
