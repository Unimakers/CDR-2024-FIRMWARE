#pragma once
#include <AccelStepper.h>

// #ifndef _MOTION_H
// #define _MOTION_H
// #endif




class Motion
{
private:
    AccelStepper *left, *right;

public:
    Motion(AccelStepper *L, AccelStepper *R);
    ~Motion();
    void MoveLine();
    void MoveArc();
    void Turn();


};


