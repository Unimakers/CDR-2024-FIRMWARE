#include "motion.h"


Motion::Motion(AccelStepper &L, AccelStepper &R):left(L), right(R)
{

}

Motion::~Motion()
{
}


void Motion::SetSpeed(float Speed){
    left.setMaxSpeed(Speed);
    right.setMaxSpeed(Speed);
}

void Motion::SetMaxAcceleration(float a){
    left.setAcceleration(a);
    right.setAcceleration(a);
}


/// @brief Makes the robot move in a straight line
/// @param distance the distance in steps to do, will be in mm in future version as seen in next functions
void Motion::MoveLine(int distance){
    
    left.move(distance);
    right.move(-distance);
}

void Motion::Turn(int angle){
    // la formule de longeur d'un arc de cercle (la distance a parcourir pour une roue)
    // est 2*Pi*A**R/360, il faudrait voir si il n'existe pas de formules sans divisions

    int MMToDo = (2*3.14*angle*RAYON)/360;
    int StepsToDo = MMToDo*STEPPERMM;
    left.move(StepsToDo);
    right.move(StepsToDo);
}


// verifier si les signes sont dans le bon sens lors du mise en route officielle

/// @brief Makes an arc movement
/// @param side to wich side
/// @param angle to what extend (negative value will be backwards)
/// @param radius the raduis of the part circle drawed
void Motion::MoveArc(int side , int angle, int radius){
    int halfRayon= RAYON*0.5; // only calculate the float once to prevent multiple floats beign calculated and overflowed into the abyss
    int BigArc = radius+halfRayon;
    int SmallArc = radius-halfRayon;

    int MMtoDoBigArc = (2*3.14*angle*BigArc)/360;
    int MMtoDoSmallArc = (2*3.14*angle*SmallArc)/360;
    
    int StepsToDoBigArc = MMtoDoBigArc*STEPPERMM;
    int StepsToDoSmallArc = MMtoDoSmallArc*STEPPERMM;



    switch(side){
        case Left_Arc:
            left.move(StepsToDoBigArc);
            right.move(StepsToDoSmallArc);
        break;
        case Right_Arc:
            left.move(StepsToDoSmallArc);
            right.move(StepsToDoBigArc);
        break;
        default:
            Serial.println("error, no declared type of arc movement");
    }
}


/// @brief Run the robot
/// Updates the two motors to run at the same time
void Motion::Run(){
    left.run();
    right.run();
}