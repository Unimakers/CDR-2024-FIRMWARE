#include <Arduino.h>
#include <Wire.h>

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
            nDevices += 1;
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