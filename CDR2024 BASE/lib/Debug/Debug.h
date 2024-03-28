#include "UniBoardDef.h"
#include <Arduino.h>

// in case you want to debug the nappes, use this function!
void debugNappes() {
	Serial.print("NAPPE1: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE1));
	Serial.print("NAPPE2: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE2));
	Serial.print("NAPPE3: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE3));
	Serial.print("NAPPE4: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE4));
	Serial.print("NAPPE5: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE5));
	Serial.print("NAPPE6: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE6));
	Serial.print("NAPPE7: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE7));
	Serial.print("NAPPE8: ");
	Serial.println(digitalRead(PIN::Nappe::NAPPE8));
	Serial.println("============");
	delay(1000);
}


void print_mesure()
{
  Serial.print(">lidar:");
  Serial.print(mesure.distance * cos(mesure.angle * DEG_TO_RAD));
  Serial.print(":");
  Serial.print(mesure.distance * sin(mesure.angle * DEG_TO_RAD));
  Serial.print(":");
  Serial.println("|xy");
}
