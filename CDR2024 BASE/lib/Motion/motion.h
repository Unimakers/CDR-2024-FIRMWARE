#pragma once
#include <AccelStepper.h>

#ifndef _MOTION_H
#define _MOTION_H
#endif

#define RAYON 145
#define STEPPERMM 6.26

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

        AccelStepper left, right;
        RobotDistance DistanceToGo();
        const int Enpin = 0;
        bool PendingStop = false;

    public:
        
        void SetSpeed(float Speed);
        void SetMaxAcceleration(float a);

        bool TargetReached();

        void MoveLine(int distance);
        void MoveArc(int side , int angle, int radius);
        void Turn(int angle);

        void Stop();
        bool GetPendingStop();
        void Resume();

        void Enable();
        void Disable();
        void Run();

    //Singleton
    public:
        static inline Motion& instance(){return m_instance;}

        Motion(const Motion&) = delete;
        Motion(Motion&&) = delete;
        Motion& operator=(const Motion&) = delete;
        Motion& operator=(Motion&&) = delete;

    private:
        static Motion m_instance;
        Motion();
};


