#include <Arduino.h>
#include <UniBoardDef.h>
#include <AccelStepper.h>

AccelStepper NEMAL(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper NEMAR(AccelStepper::DRIVER, STEP2, DIR2);


void setup() {
  Serial.begin(9600);
  pinMode(TIR, INPUT_PULLUP);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, HIGH);


  NEMAL.setMaxSpeed(200.0);
  NEMAL.setAcceleration(200.0);
  

  Serial.println("Waiting for button press");
  while(digitalRead(TIR)==1){

  }
  
  NEMAL.moveTo(100);
  digitalWrite(EN, LOW);
  Serial.println("Start");
}

void loop() {

    NEMAL.run();
    if(NEMAL.distanceToGo()==0){
      digitalWrite(EN, HIGH);
    }

    if(digitalRead(TIR)==0){
      digitalWrite(EN, LOW);
      NEMAL.move(1000);
    }
}

