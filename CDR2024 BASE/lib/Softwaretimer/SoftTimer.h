#pragma once
#ifndef SOFTTIMER_H
#define _SOFTTIMER_H
#endif

#include <Arduino.h>

class SoftTimer{


    protected: 
        unsigned long PreviousMillis;
        unsigned long Interval;
        bool end;

    public:
        SoftTimer();
        ~SoftTimer();

        void SetTimer(long Milliseconds);
        void StartTimer();
        void StopTimer();
        void updateTimer();

        bool IsEnded();



};