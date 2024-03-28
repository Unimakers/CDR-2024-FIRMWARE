
#include "Baril.h"
#include "UniBoardDef.h"

Baril Baril::m_instance;

Baril::Baril() : motor(AccelStepper::DRIVER, PIN::Steppers::STEP3, PIN::Steppers::DIR3){

    motor.setPinsInverted(false);
    motor.setMaxSpeed(100);
    motor.setAcceleration(200);
    pinMode(PIN::Nappe::Nappe1);
    
}

void Baril::Init(){


}

void Baril::Probe(){
    motor.move(400);
}

bool Baril::isProbing(){


}

void Baril::Run(){


    motor.run();
}