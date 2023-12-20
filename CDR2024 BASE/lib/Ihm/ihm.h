#pragma once
#ifndef _IHM_H
#define _IHM_H
#endif

#include <Arduino.h>
#include <UniBoardDef.h>



class IHM{
    public:
        IHM();
        ~IHM();
        bool GetTirette();
        bool GetButton(int btn);

};
