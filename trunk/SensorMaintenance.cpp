#include "SensorMaintenance.h"

void SensorMaintenance::setup() {
	nLastAvailable = -1000*360;
}

bool SensorMaintenance::available() {
  return (millis()-nLastAvailable) >= 16000;
}

char* SensorMaintenance::getValue() {
  nLastAvailable = millis();
  return "0";
}