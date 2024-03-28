
#include "Baril.h"
#include "UniBoardDef.h"

Baril Baril::m_instance;

Baril::Baril() : motor(AccelStepper::DRIVER, PIN::Steppers::STEP3, PIN::Steppers::DIR3){

    motor.setPinsInverted(false);
    motor.setMaxSpeed(100);
    motor.setAcceleration(200);
    pinMode(PIN::Nappe::NAPPE1, INPUT_PULLUP);
    
}

void Baril::Init(){


}

// ugly code
void Baril::Probe(){
	motor.move(150);

	while (motor.distanceToGo() != 0) {
		Run();
	}

    motor.move(1600);

	do {
		Run();
	} while (!isCalibrated());

	motor.move(50);

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

void Baril::Run(){


    motor.run();
}
