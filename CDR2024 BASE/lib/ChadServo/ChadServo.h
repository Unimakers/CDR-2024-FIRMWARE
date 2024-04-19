#pragma once

#ifndef _CHADSERVO_H
#define _CHADSERVO_H
#endif

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <AccelStepper.h>
#include "UniBoardDefV4.h"
#include "Baril.h"

  /*
      MOTEUR PIN 1 : réglage hauteur,      bas ~150 haut ~450
      MOTEUR PIN 2 : réglage pince droite, droite ~450 gauche ~150
      MOTEUR PIN 3 : réglage pince gauche, droite ~450 gauche ~150
      MOTEUR PIN 4 : réglage angle,        droite ~150 gauche ~450
  */





// Permet de saisir une fleur et de la mettre dans un pot sur le bariller
// void mettre_fleur_pot() {
//     switch (etape_actuelle_servo) {
//         case 0:
//             servo_xy(SERVO_MOVE_PINCE, 63);
//             servo_xy(SERVO_PINCE_DROITE, 40);
//             servo_xy(SERVO_PINCE_GAUCHE, 75);

//             temps_debut_servo = millis();
//             etape_actuelle_servo = 1;
//             baril_move(75);
//             break;

//         case 1:
//             if (millis() - temps_debut_servo >= 1000) {
//                 servo_z(SERVO_Z_GAUCHE, 0);

//                 temps_debut_servo = millis();
//                 etape_actuelle_servo = 2;
//             }
//             break;

//         case 2:
//             if (millis() - temps_debut_servo >= 1000) {
//                 servo_xy(SERVO_PINCE_DROITE, 15);
//                 servo_xy(SERVO_PINCE_GAUCHE, 100);

//                 temps_debut_servo = millis();
//                 etape_actuelle_servo = 3;
//             }
//             break;

//         case 3:
//             if (millis() - temps_debut_servo >= 1000) {
//                 servo_z(SERVO_Z_GAUCHE, 100);

//                 temps_debut_servo = millis();
//                 etape_actuelle_servo = 4;
//                 baril_move(25);
//             }
//             break;

//         case 4:
//             if (millis() - temps_debut_servo >= 1000) {
//                 servo_xy(SERVO_MOVE_PINCE, 3);

//                 temps_debut_servo = millis();
//                 etape_actuelle_servo = 5;
//             }
//             break;

//         case 5:
//             if (millis() - temps_debut_servo >= 1000) {
//                 servo_xy(SERVO_PINCE_DROITE, 35);
//                 servo_xy(SERVO_PINCE_GAUCHE, 65);

//                 temps_debut_servo = millis();
//                 etape_actuelle_servo = 6;
//             }
//             break;

//         case 6:
//             if (millis() - temps_debut_servo >= 1000) {
//                 servo_xy(SERVO_MOVE_PINCE, 63);

//                 etape_actuelle_servo = 0;
//             }
//             break;
//         default:
//             break;
//     }
// }


class PinceAscenseur{
    public:
        PinceAscenseur(int z, int Dl,int Dr, int Polar);
        ~PinceAscenseur();

        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

        int Zaxis;
        int Doigt_gauche;
        int Doigt_Droite;
        int Polaire;

        void setGrablimits(int Open, int Close);
        void setLiftLimits(int Down, int Up);
        void setTurnLimits(int In, int Out);
        void invertZLimits();
        void invertPolarLimits();

        void begin();
        void grab();
        void ungrab();
        void GrabP(int pourcent);
        void lift();
        void drop();
        void turnIn();
        void turnOut();


    private:
        int OpenLimit = 30, CloseLimit = 100;
        int DownLimit = 0, UpLimit = 100;
        int OutLimit = 0, InLimit=100;

    protected:

};