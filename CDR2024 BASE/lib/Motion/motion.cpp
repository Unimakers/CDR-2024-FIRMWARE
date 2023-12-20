#include "motion.h"
#include <AccelStepper.h>



motion::motion(AccelStepper &L, AccelStepper &R)
{
    //get the two motors
    left = &L;
    right = &R;
}

motion::~motion()
{
}

void MoveLine(){
    
    left.moveTo();
    right.moveTo();


}