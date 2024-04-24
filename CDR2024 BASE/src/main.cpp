#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "UniBoardDefV4.h"
#include "ChadServo.h"

PinceAscenseur PinceGauche(PIN::PinceGauche::Z,PIN::PinceGauche::DOIGTGAUCE,PIN::PinceGauche::DOIGTDROITE,PIN::PinceGauche::POLAR);
PinceAscenseur PinceDroite(PIN::PinceDroite::Z,PIN::PinceDroite::DOIGTGAUCHE,PIN::PinceDroite::DOIGTDROITE,PIN::PinceDroite::POLAR);




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

void setup(){

    pinMode(PIN::Nappe::NAPPE2,INPUT);
    pinMode(PIN::BUZZER,OUTPUT);


    Wire.begin(PIN::I2C::SDA, PIN::I2C::SCL);
    delay(500);


    PinceGauche.begin();
    PinceGauche.setTurnLimits(0,75);
    PinceDroite.begin();
    PinceDroite.setTurnLimits(25,100);
    PinceDroite.invertPolarLimits();

    PinceDroite.invertZLimits();

    Serial.begin(115200);
    tone(PIN::BUZZER,1000,500);
    delay(1000);



}


void loop(){
    int tmp;
    //Serial.printf(">distance:%i\n",analogRead(PIN::Nappe::NAPPE7));
    delay(100);

    tmp = MobileAverage();
    Serial.printf(">distance:%i\n",tmp);
    if (tmp>3100)
    {
        PinceGauche.grab();
    }else if (tmp<900)
    {
        PinceGauche.ungrab();
    }
    
    
}