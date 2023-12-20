#pragma once
#include <AccelStepper.h>

// #ifndef _MOTION_H
// #define _MOTION_H
// #endif

#define RAYON 80
#define STEPPERMM 120

typedef enum
{
    Left_Arc=0,
    Right_Arc=1
} Arc;


class Motion
{
protected:
    AccelStepper &left, &right;

public:
    Motion(AccelStepper &L, AccelStepper &R);
    ~Motion();
    
    
    void SetSpeed(float Speed);
    void SetMaxAcceleration(float a);

    void MoveLine(int distance);
    void MoveArc(int side , int angle, int radius);
    void Turn(int angle);
    void Run();


};


