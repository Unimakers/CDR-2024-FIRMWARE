#include <Arduino.h>
#include <UniBoardDef.h>
#include <AccelStepper.h>

AccelStepper NEMAL(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper NEMAR(AccelStepper::DRIVER, STEP2, DIR2);


void setup() {Serial.begin(9600);
    pinMode(TIR, INPUT_PULLUP);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, HIGH);

    NEMAL.setMaxSpeed(10000);
    NEMAL.setAcceleration(1000);
    NEMAR.setMaxSpeed(10000);
    NEMAR.setAcceleration(1000);

    Serial.println("Waiting for button press");
    while (digitalRead(TIR) == 1);

    NEMAL.moveTo(100);
    NEMAR.moveTo(-100);
    digitalWrite(EN, LOW);
    Serial.println("Start");
}

void loop() {
    NEMAL.run();
    NEMAR.run();
    if (NEMAL.distanceToGo() == 0 && NEMAR.distanceToGo() == 0) {
        digitalWrite(EN, HIGH);
    }

    if (digitalRead(TIR) == 0) {
        digitalWrite(EN, LOW);
        NEMAL.move(10000);
        NEMAR.move(10000);
    }
}
