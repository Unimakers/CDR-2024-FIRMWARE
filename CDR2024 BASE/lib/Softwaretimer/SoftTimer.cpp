#include "SoftTimer.h"

SoftTimer::SoftTimer(){

    PreviousMillis = 0;
    Interval = 0;
    end = true;


}

SoftTimer::~SoftTimer(){
    
}

void SoftTimer::SetTimer(long Milliseconds){
    Interval = Milliseconds;
    return;
}

void SoftTimer::StartTimer(){
    PreviousMillis = millis();
    end = false;
    return;
}

void SoftTimer::StopTimer(){

    end = true;
    return;

}

void SoftTimer::updateTimer(){
    if(end){ // if already ended then spare resources and return directly
        return;
    }else{ // else check if timer has passed
        if(millis() - PreviousMillis > Interval){
            end = true;
        }
    }
    return;
}

bool SoftTimer::IsEnded(){

    return end;

}