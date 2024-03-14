#include "ihm.h"



IHM::IHM(){
    pinMode(PIN::Inputs::TIR, INPUT_PULLUP);
    pinMode(btn1,INPUT_PULLUP);
}

IHM::~IHM(){

}
/// @brief Get the state of the trigger
/// @return True if present, false if absent
bool IHM::GetTirette(){
    bool State = digitalRead(PIN::Inputs::TIR);
    return !State;
}
/// @brief Gets the state of the lonely button
/// @param btn By default this value is one, so if left empty, defaults to main button
/// @return returns 1 if true, 0 if false
bool IHM::GetButton(int btn=1){
    bool State = digitalRead(btn);
    return State;
}