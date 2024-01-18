#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

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

// Permet de faire monter sur l'axe Z un servo
void servo_z(int idServo, int pourcentage) {
    pourcentage = constrain(pourcentage, 0, 100);
    pourcentage = map(pourcentage, 0, 100, 210, 456);
    pwm.setPWM(idServo, 0, pourcentage);
}

// Permet de faire tourner vers la gauche un servo
void servo_xy(int idServo, int pourcentage) {
    pourcentage = constrain(pourcentage, 0, 100);
    pourcentage = map(pourcentage, 0, 100, 150, 450);
    pwm.setPWM(idServo, 0, pourcentage);
}

void mettre_fleur_pot() {
    servo_z(SERVO_HAUTEUR, 0);
    servo_xy(SERVO_MOVE_PINCE, 70);
    servo_xy(SERVO_PINCE_DROITE, 35);
    servo_xy(SERVO_PINCE_GAUCHE, 65);
    delay(1000);
    servo_xy(SERVO_PINCE_DROITE, 0);
    servo_xy(SERVO_PINCE_GAUCHE, 100);
    delay(1000);
    servo_z(SERVO_HAUTEUR, 60);
    delay(1000);
    servo_xy(SERVO_MOVE_PINCE, 30);
    delay(1000);
    servo_xy(SERVO_PINCE_DROITE, 35);
    servo_xy(SERVO_PINCE_GAUCHE, 65);
    delay(1000);
    servo_z(SERVO_HAUTEUR, 100);
    delay(1000);
    servo_xy(SERVO_MOVE_PINCE, 70);
    delay(1000);
}
