#pragma once
#ifndef _IHM_H
#define _IHM_H
#endif

#include <Arduino.h>
#include <UniBoardDefV4.h>




class IHM{
    public:
        IHM();
        ~IHM();
        bool GetTirette();
        bool GetButton(int btn);
        void Buzzer();

};
