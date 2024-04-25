#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "motion.h"

#include "UniBoardDefV4.h"
#include "ChadServo.h"

PinceAscenseur PinceGauche(PIN::PinceGauche::Z,PIN::PinceGauche::DOIGTGAUCE,PIN::PinceGauche::DOIGTDROITE,PIN::PinceGauche::POLAR);
PinceAscenseur PinceDroite(PIN::PinceDroite::Z,PIN::PinceDroite::DOIGTGAUCHE,PIN::PinceDroite::DOIGTDROITE,PIN::PinceDroite::POLAR);


Motion& Robot = Motion::instance();

int MobileAverage(){
    static int u[4] = {0,0,0,0};
    static int index = 0;
    static int total;
    if(index > 3){
        index = 0;
    }
    total -= u[index];
    u[index] = analogRead(PIN::Nappe::NAPPE7);
    total += u[index];
    index++;

    return total/4;
}


bool FindPlant(){
    //static int index = 0;
    static bool Found = false;
    static int measure=0;
    int tmp = analogRead(PIN::Nappe::NAPPE7);
    Serial.println(tmp);

    if(Found){
        Robot.MoveLine(100);
        Found = false;
        return true;
    }

    if (tmp> measure || tmp<1000)
    {
        measure = tmp;
        Robot.Turn(-5);
        return false;

    }else if (tmp < (measure - 200)&& measure >1000)
    {
        Robot.Turn(15);
        Serial.println("Plant Found");
        Found = true;
        return false;
    }
    
    return false;
}


void setup(){

    pinMode(PIN::Nappe::NAPPE2,INPUT);
    pinMode(PIN::BUZZER,OUTPUT);
    pinMode(PIN::Inputs::btn1,INPUT_PULLUP);


    Wire.begin(PIN::I2C::SDA, PIN::I2C::SCL);
    delay(1000);

    Robot.SetSpeed(5000);
    Robot.SetMaxAcceleration(5000);
    Robot.Disable();


    PinceGauche.begin();
    PinceGauche.setTurnLimits(0,75);
    PinceDroite.begin();
    PinceDroite.setTurnLimits(25,100);
    PinceDroite.invertPolarLimits();

    PinceDroite.invertZLimits();

    Serial.begin(115200);
    tone(PIN::BUZZER,1000,500);
    delay(1000);

    while (digitalRead(PIN::Inputs::btn1))
    {
        
    }
    Robot.Enable();
    PinceGauche.ungrab();
    



}


void loop(){
    int tmp;
    static int index = 0;
    //Serial.printf(">distance:%i\n",analogRead(PIN::Nappe::NAPPE7));

    // delay(100);
    // tmp = MobileAverage();
    // Serial.printf(">distance:%i\n",tmp);
    // if (tmp>3100)
    // {
    //     PinceGauche.grab();
    // }else if (tmp<900)
    // {
    //     PinceGauche.ungrab();
    // }

    if (Robot.TargetReached() )
    {
        if(index == 0){

            if(FindPlant()){
            index = 1;
            }

        }else if(index==1){
            
            PinceGauche.grab();
            index = 2;

        }


    }
    
    

    Robot.Run();
}