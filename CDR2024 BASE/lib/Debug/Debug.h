#include <UniBoardDefV4.h>
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


// void print_mesure()
// {
//   Serial.print(">lidar:");
//   Serial.print(mesure.distance * cos(mesure.angle * DEG_TO_RAD));
//   Serial.print(":");
//   Serial.print(mesure.distance * sin(mesure.angle * DEG_TO_RAD));
//   Serial.print(":");
//   Serial.println("|xy");
// }

// Scan en ping les adresses possibles afin de trouver des périphs en I2C
void scan_i2c() {
    unsigned char error, address;
    int nDevices = 0;

    Serial.println("Scan...");

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C found, address: 0x");

            if (address < 16) {
                Serial.print("0");
            }

            Serial.println(address, HEX);
            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address: 0x");

            if (address < 16) {
                Serial.print("0");
            }

            Serial.println(address, HEX);
        }
    }

    if (nDevices == 0) {
        Serial.println("No I2C found");
    } else {
        Serial.print("nDevices: ");
        Serial.println(nDevices);
    }
}