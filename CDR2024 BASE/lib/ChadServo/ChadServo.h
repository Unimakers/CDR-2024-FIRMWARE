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


class PinceAscenseur{
    public:
        PinceAscenseur(int z, int Dl,int Dr, int Polar,int flipper);
        ~PinceAscenseur();

        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

        int Zaxis;
        int Doigt_gauche;
        int Doigt_Droite;
        int Polaire;
        int flipper;

        bool toggle = false;

        void setGrablimits(int Open, int Close);
        void setLiftLimits(int Down, int Up);
        void setTurnLimits(int In, int Out);
        void invertZLimits();
        void invertPolarLimits();

        void flipout();
        void flipin();
        void toggleflip();


        void begin();
        void grab();
        void ungrab();
        void GrabP(int pourcent);
        void lift();
        void drop();
        void dropPlanters();
        void turnIn();
        void turnOut();


    private:
        int OpenLimit = 30, CloseLimit = 100;
        int DownLimit = 55, UpLimit = 100, MaxDown = 0, MaxUp= 100;
        int OutLimit = 0, InLimit=100;
        bool In =false ;

    protected:

};