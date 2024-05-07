#include "ChadServo.h"
       


PinceAscenseur::PinceAscenseur(int z, int Dl,int Dr, int Polar ,int flip ){

    Zaxis = z;
    Doigt_gauche =Dl;
    Doigt_Droite =Dr;
    Polaire = Polar;
    flipper = flip;

}

PinceAscenseur::~PinceAscenseur(){

    
}

void PinceAscenseur::setTurnLimits(int In, int Out){
    InLimit = In;
    OutLimit = Out;

}

void PinceAscenseur::begin(){

    pwm.begin();
    delay(1000);
    pwm.setOscillatorFrequency(25000000); // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/examples/servo/servo.ino#L49
    pwm.setPWMFreq(SERVO_FREQ_HZ);

}


void PinceAscenseur::grab(){
    int pourcentageleft,pourcentageright;
    pourcentageleft = map(CloseLimit, 0, 100, 210, 500);
    pourcentageright = map(CloseLimit, 0, 100, 500, 210);
    pwm.setPWM(Doigt_Droite, 0, pourcentageright);
    pwm.setPWM(Doigt_gauche,0,pourcentageleft);
}

void PinceAscenseur::ungrab(){

    int pourcentageleft,pourcentageright;
    pourcentageleft = map(OpenLimit, 0, 100, 210, 500);
    pourcentageright = map(OpenLimit, 0, 100, 500, 210);
    pwm.setPWM(Doigt_Droite, 0, pourcentageright);
    pwm.setPWM(Doigt_gauche,0,pourcentageleft);

}

void PinceAscenseur::GrabP(int pourcent){


}

void PinceAscenseur::invertZLimits(){
    int tmp;
    tmp = DownLimit;
    DownLimit = UpLimit;
    UpLimit = tmp;
    tmp = MaxUp;
    MaxUp = MaxDown; 
    MaxDown = tmp;

    return;
}


void PinceAscenseur::lift(){
    
    int pourcentage = constrain(UpLimit, 0, 100);
    pourcentage = map(pourcentage, 0, 100, 210, 500);
    pwm.setPWM(Zaxis, 0, pourcentage);

}

void PinceAscenseur::setLiftLimits(int Down, int Up){
    DownLimit = Down;
    UpLimit = Up;


}

void PinceAscenseur::drop(){
    int pourcentage;
    if(In){
        pourcentage = constrain(DownLimit, 0, 100);
    }else
    {
        pourcentage = constrain(MaxDown, 0, 100);
    }
    
    Serial.printf("Servo pourcentage %i\n",pourcentage);
    pourcentage = map(pourcentage, 0, 100, 210, 456);
    pwm.setPWM(Zaxis, 0, pourcentage);
}

void PinceAscenseur::dropPlanters(){
    int pourcentage;
    pourcentage = constrain(DownLimit, 0, 100);
    Serial.printf("Servo pourcentage %i\n",pourcentage);
    pourcentage = map(pourcentage, 0, 100, 210, 456);
    pwm.setPWM(Zaxis, 0, pourcentage);
}

void PinceAscenseur::turnIn(){
    In = true;
    int pourcentage = constrain(InLimit, 0, 100);
    pourcentage = map(pourcentage, 0, 100, 150, 456);
    pwm.setPWM(Polaire, 0, pourcentage);
}

void PinceAscenseur::turnOut(){
    In = false;
    int pourcentage = constrain(OutLimit, 0, 100);
    pourcentage = map(pourcentage, 0, 100, 150, 456);
    pwm.setPWM(Polaire, 0, pourcentage);
}
void PinceAscenseur::invertPolarLimits(){
    int tmp;
    tmp = OutLimit;
    OutLimit = InLimit;
    InLimit = tmp;
    return;
}

void PinceAscenseur::flipout(){

    if (toggle){
            int pourcentage = constrain(100, 0, 100);
            pourcentage = map(pourcentage, 0, 100, 150, 456);
            pwm.setPWM(flipper,0, pourcentage);// 100 est fermé

    }else{
        int pourcentage = constrain(50, 0, 100);
        pourcentage = map(pourcentage, 0, 100, 150, 456);
        pwm.setPWM(flipper,0, pourcentage);// 100 est fermé

    }
}

void PinceAscenseur::flipin(){

    if (toggle){
            int pourcentage = constrain(50, 0, 100);
            pourcentage = map(pourcentage, 0, 100, 150, 456);
            pwm.setPWM(flipper,0, pourcentage);// 100 est fermé

    }else{
        int pourcentage = constrain(100, 0, 100);
        pourcentage = map(pourcentage, 0, 100, 150, 456);
        pwm.setPWM(flipper,0, pourcentage);// 100 est fermé

    }

}

void PinceAscenseur::toggleflip(){
    toggle = !toggle;
}