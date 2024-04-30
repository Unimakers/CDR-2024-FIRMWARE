#include <Arduino.h>
#include <Wire.h>
#include "BNO08X.h"
#include "UniBoardDefV4.h"
#include "motion.h"
#include "SoftTimer.h"

SoftTimer BnoTimer;
Motion& Robot = Motion::instance();


void MotorRun(void *pvParameters){
    static bool dir;

    for(;;){

        if(BnoTimer.IsEnded()){
            HandleBNO();
            BnoTimer.StartTimer();
        }

        // if(Robot.TargetReached()){
        //     if(dir){
        //         Robot.Turn(180);
                
        //     }else{
        //         Robot.Turn(-180);
        //     }
        //     dir=!dir;
            
        // }
        BnoTimer.updateTimer();

    }

}

void setup(){

    Serial.begin(115200);
    pinMode(PIN::Inputs::btn1,INPUT_PULLUP);
    Wire.begin(PIN::I2C::SDA, PIN::I2C::SCL);

    delay(1000);
    BNO_init();
    Robot.Disable();
    Robot.SetSpeed(500);
    Robot.SetMaxAcceleration(500);
    tone(PIN::BUZZER, 440, 100);

    Serial.println("started");

    //Robot.Enable();
    Robot.Disable();
    

    BnoTimer.SetTimer(100);
    while (digitalRead(PIN::Inputs::btn1))
    {
        
    }
    tone(PIN::BUZZER, 520, 100);


    BnoTimer.StartTimer();

    xTaskCreatePinnedToCore(MotorRun, "MotorRun", 10000, NULL, 0, NULL, 0);
    Robot.MoveLine(-1500);



}

void loop(){


    Robot.Run();



}