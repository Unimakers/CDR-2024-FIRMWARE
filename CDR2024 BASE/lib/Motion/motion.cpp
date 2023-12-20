#include "motion.h"



Motion::Motion(AccelStepper *L, AccelStepper *R)
{
    //get the two motors
    left = L;
    right = R;
}

Motion::~Motion()
{
}

void Motion::MoveLine(){
    
    *left.moveTo(100);
    right->moveTo(-100);


}