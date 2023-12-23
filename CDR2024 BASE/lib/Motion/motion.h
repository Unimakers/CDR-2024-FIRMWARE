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

typedef struct{
    long LeftDistance;
    long RightDistance;
}RobotDistance;


class Motion
{
    protected:

        RobotDistance LeftOverDistance;

        AccelStepper &left, &right;
        RobotDistance DistanceToGo();
        const int Enpin = 0;
        bool PendingStop = false;

    public:
        Motion(AccelStepper &L, AccelStepper &R);
        Motion(AccelStepper &L, AccelStepper &R,int enablePin);
        ~Motion();
        
        void SetSpeed(float Speed);
        void SetMaxAcceleration(float a);

        bool TargetReached();

        void MoveLine(int distance);
        void MoveArc(int side , int angle, int radius);
        void Turn(int angle);

        void Stop();

        void Enable();
        void Disable();
        void Run();


};


