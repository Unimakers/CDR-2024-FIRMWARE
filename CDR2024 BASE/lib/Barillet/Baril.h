#pragma once
#ifndef _BARIL_H
#define _BARIL_H
#endif

#include <AccelStepper.h>

class Baril
{
    protected:

        AccelStepper motor;
        /* data */
    public:

        void Init();
        void Probe();
        void moveTo(int pourcentage);
        void Quarter();

        bool isCalibrated();

        void Run();




//singleton

    public:
        static inline Baril& instance(){return m_instance;}

        Baril(const Baril&) = delete;
        Baril(Baril&&) = delete;
        Baril& operator=(const Baril&) = delete;
        Baril& operator=(Baril&&) = delete;

    private:
        static Baril m_instance;
        Baril();


};
