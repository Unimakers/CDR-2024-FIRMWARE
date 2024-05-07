#pragma once
#include <Arduino.h>
#include <Adafruit_BNO08x.h>

#include <cmath>

#define BNO08X_RESET -1

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;
long reportIntervalUs = 5000;

void setReports(void) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(SH2_ARVR_STABILIZED_GRV)) {
    Serial.println("Could not enable game vector");
  }
}


void BNO_init(){

  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  setReports();

}

void HandleBNO(){

  if (bno08x.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }
  
  if (! bno08x.getSensorEvent(&sensorValue)) {
    return;
  }
  
  switch (sensorValue.sensorId) {
    
    case SH2_GAME_ROTATION_VECTOR:
      Serial.printf(">r: %f\n",sensorValue.un.arvrStabilizedGRV.real);
      Serial.printf("> i: %f\n",sensorValue.un.arvrStabilizedGRV.i);
      Serial.printf(">j: %f\n",sensorValue.un.arvrStabilizedGRV.j);
      Serial.printf(">k: %f\n",sensorValue.un.arvrStabilizedGRV.k);
      break;
  }

}