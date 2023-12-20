#include "ihm.h"
#include "UniBoardDef.h"
#include <Arduino.h>


IHM::IHM(){

}

IHM::~IHM(){

}


bool getTirrette(){
    bool State = digitalRead(TIR);
    return State;
}

bool getButton(int btn=1){
    bool State = digitalRead(btn);
}