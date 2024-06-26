
#include "Baril.h"
#include <UniBoardDefV4.h>


Baril Baril::m_instance;

Baril::Baril() : motor(AccelStepper::DRIVER, PIN::Steppers::STEP4, PIN::Steppers::DIR4){

    motor.setPinsInverted(false);
    motor.setMaxSpeed(1000);
    motor.setAcceleration(2000);
    pinMode(PIN::Nappe::NAPPE1, INPUT_PULLUP);
    
}

void Baril::Init(){

    Probe();
    motor.setMaxSpeed(1000);
    motor.setAcceleration(4000);

}

// ugly code
void Baril::Probe(){
    
	if(isCalibrated()){
		motor.move(-100);
	}

	while (motor.distanceToGo() != 0) {
		Run();
	}

    motor.move(2600);

	do {
		Run();
	} while (!isCalibrated());

	motor.move(60);

	while (motor.distanceToGo() != 0) {
		Run();
	}

	
}

bool Baril::isCalibrated(){
	switch (digitalRead(PIN::Nappe::NAPPE1)) {
		case 0:
			return true;
			break;
		case 1:
			return false;
			break;
		default:
			Serial.println("Impossible de lire le capteur NAPPE1");
			return false;
			break;
	}
}



void Baril::Quarter(){
    motor.move(400);

}

void Baril::Half(){
	motor.move(800);

}

void Baril::Run(){
    motor.run();
}


bool Baril::TargetReached(){
	if(motor.distanceToGo()== 0){
		return true;

	}
	return false;


}