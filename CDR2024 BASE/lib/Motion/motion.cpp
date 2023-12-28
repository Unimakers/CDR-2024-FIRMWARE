#include "motion.h"


Motion::Motion(AccelStepper &L, AccelStepper &R):left(L), right(R)
{
    LeftOverDistance.LeftDistance = 0;
    LeftOverDistance.RightDistance = 0;
}

Motion::Motion(AccelStepper &L, AccelStepper &R,int enablePin):left(L), right(R),Enpin(enablePin)
{
    pinMode(Enpin,OUTPUT);
    digitalWrite(Enpin, HIGH);
    LeftOverDistance.LeftDistance = 0;
    LeftOverDistance.RightDistance = 0;
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
/// @brief Makes the robot turn auround on its center point
/// @param angle The relative angle of rotation
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
/// @brief Stops the robot in a slow manner
void Motion::Stop(){
    if(TargetReached()){ // means that the robot is already not moving so do not calculate
        PendingStop = false;
        LeftOverDistance.LeftDistance=0;
        LeftOverDistance.RightDistance=0;
        return;
    }
    if(PendingStop){ // means we have already calculated the stop sequence
        return;
    }else{
        PendingStop = true; 
        LeftOverDistance.LeftDistance=left.distanceToGo(); //Store the Distance left to go
        LeftOverDistance.RightDistance=right.distanceToGo(); // Store the Distance left to go
        //Serial.println(LeftOverDistance.LeftDistance);
        //Serial.println(LeftOverDistance.RightDistance);
        left.stop();
        right.stop();
        // as the stop command has set a new distanceToGo, we need to remove this distance from the pending task
        LeftOverDistance.LeftDistance-=left.distanceToGo(); //remove the distance done by the stop command
        LeftOverDistance.RightDistance-=right.distanceToGo(); // remove the distance done by the stop command
        //Serial.println("Stop incoming");
    }
}
/// @brief Should be called after a stop command if the robot needs to finsih last task
void Motion::Resume(){


    PendingStop = false;
    //If the resume command has been called when the robot was still decelrating, add the remaing distance of the stop command
    left.move(LeftOverDistance.LeftDistance+left.distanceToGo());
    right.move(LeftOverDistance.RightDistance+right.distanceToGo());

}


RobotDistance Motion::DistanceToGo(){

    RobotDistance tmp;
    tmp.LeftDistance = left.distanceToGo();
    tmp.RightDistance = right.distanceToGo();

    return tmp;
}
/// @brief Checks if both motors have reached their targets
/// @return True if valid, false otherwise
bool Motion::TargetReached(){

    RobotDistance tmp;

    tmp = DistanceToGo();

    if(tmp.LeftDistance == 0 && tmp.RightDistance == 0){
        return true;
    }else{
        return false;
    }

}
/// @brief Very easy way to Enable the motors
void Motion::Enable()
{
    digitalWrite(Enpin,LOW);

}
/// @brief Very easy way to disable the motors,
/// this will also set the movement to 0
void Motion::Disable(){

    digitalWrite(Enpin,HIGH);
    left.move(0);
    right.move(0);

}

/// @brief Run the robot,
/// Updates the two motors to run at the same time
void Motion::Run(){
    left.run();
    right.run();
}