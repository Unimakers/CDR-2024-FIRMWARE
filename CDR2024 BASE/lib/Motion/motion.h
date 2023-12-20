#ifndef _MOTION_H
#define _MOTION_H
#endif

#pragma once


class motion
{
private:
    AccelStepper *left, *right;

public:
    motion(AccelStepper &L, AccelStepper &R);
    ~motion();
    void MoveLine();
    void MoveArc();
    void Turn();


};


