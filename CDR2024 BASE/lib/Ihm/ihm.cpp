#include "ihm.h"



IHM::IHM(){
    pinMode(TIR, INPUT_PULLUP);
}

IHM::~IHM(){

}

bool IHM::GetTirette(){
    return digitalRead(TIR);
}
/// @brief Gets the state of the lonely button
/// @param btn By default this value is one, so if left empty, defaults to main button
/// @return returns 1 if true, 0 if false
bool IHM::GetButton(int btn=1){
    bool State = digitalRead(btn);
    return State;
}