#include <Arduino.h>
#include <AccelStepper.h>

AccelStepper stepper1(AccelStepper::DRIVER, 2, 5);
AccelStepper stepper2(AccelStepper::DRIVER, 4, 7);

void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);

  stepper1.setAcceleration(100000);
  stepper1.setMaxSpeed(100000000);
  stepper2.setAcceleration(100000);
  stepper2.setMaxSpeed(100000000);

  digitalWrite(8,LOW);



  stepper1.move(400*15);
  stepper2.move(-400*15);

}

void loop() {

stepper1.run();
stepper2.run();

}

