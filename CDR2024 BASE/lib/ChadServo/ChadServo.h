#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
AccelStepper BARIL(AccelStepper::DRIVER, STEP3, DIR3);

unsigned long temps_debut_servo;
int etape_actuelle_servo = 0;

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

// Permet de positionner le baril sur un des 4 slots de plante
void baril_move(int pourcentage) {
    pourcentage = constrain(pourcentage, 0, 100);
    pourcentage = map(pourcentage, 0, 100, 0, 200);
    BARIL.moveTo(pourcentage);
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
    pourcentage = map(pourcentage, 0, 100, 100, 450);
    pwm.setPWM(idServo, 0, pourcentage);
}

// Permet de saisir une fleur et de la mettre dans un pot sur le bariller
void mettre_fleur_pot() {
    switch (etape_actuelle_servo) {
        case 0:
        /*
            servo_xy(SERVO_MOVE_PINCE, 63);
            servo_xy(SERVO_PINCE_DROITE, 40);
            servo_xy(SERVO_PINCE_GAUCHE, 75);
            */
            temps_debut_servo = millis();
            etape_actuelle_servo = 1;
            baril_move(75);
            break;

        case 1:
            if (millis() - temps_debut_servo >= 1000) {
                //servo_z(SERVO_HAUTEUR, 0);
                temps_debut_servo = millis();
                etape_actuelle_servo = 2;
            }
            break;

        case 2:
            if (millis() - temps_debut_servo >= 1000) {
                //servo_xy(SERVO_PINCE_DROITE, 15);
                //servo_xy(SERVO_PINCE_GAUCHE, 100);
                temps_debut_servo = millis();
                etape_actuelle_servo = 3;
            }
            break;

        case 3:
            if (millis() - temps_debut_servo >= 1000) {
                //servo_z(SERVO_HAUTEUR, 100);
                temps_debut_servo = millis();
                etape_actuelle_servo = 4;
                baril_move(25);
            }
            break;

        case 4:
            if (millis() - temps_debut_servo >= 1000) {
                //servo_xy(SERVO_MOVE_PINCE, 3);
                temps_debut_servo = millis();
                etape_actuelle_servo = 5;
            }
            break;

        case 5:
            if (millis() - temps_debut_servo >= 1000) {
                //servo_xy(SERVO_PINCE_DROITE, 35);
                //servo_xy(SERVO_PINCE_GAUCHE, 65);
                temps_debut_servo = millis();
                etape_actuelle_servo = 6;
            }
            break;

        case 6:
            if (millis() - temps_debut_servo >= 1000) {
                //servo_xy(SERVO_MOVE_PINCE, 63);
                etape_actuelle_servo = 0;
            }
            break;
        default:
            break;
    }
}
