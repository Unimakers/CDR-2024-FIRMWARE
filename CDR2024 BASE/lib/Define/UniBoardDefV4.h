#pragma once

namespace PIN{
    namespace Inputs{
        constexpr int 
            TIR = 6,
            btn1 = 7,
            btn2 = 48;
    }
    namespace Steppers{
        constexpr int
            STEP1 = 10,
            STEP2 = 46,
            STEP3 = 13,
            STEP4 = 21,
            EN = 11,
            DIR1 = 9,
            DIR2 = 3,
            DIR3 = 12,
            DIR4 = 14;
    } 
    namespace Lidar{
        constexpr int
             LIDAR_TX = 18,
             LIDAR_RX = 17,
             LIDAR_PWM = 8;
            
    }

    namespace I2C{
        constexpr int
            SDA = 4,
            SCL = 5;

    }
    namespace Nappe{
        constexpr int
            NAPPE1 = 45,
			NAPPE2 = 40,
			NAPPE3 = 41,
			NAPPE4 = 42,
			NAPPE5 = 39,
			NAPPE6 = 38,
			NAPPE7 = 1,
			NAPPE8 = 2;
    }

    namespace PinceGauche
    {   constexpr int
            Z = 1,
            DOIGTGAUCE = 3,
            DOIGTDROITE = 2,
            POLAR = 4,
            Flipper=0;
            
    }

    namespace PinceDroite{
        constexpr int
            Z = 14,
            DOIGTGAUCHE = 12,
            DOIGTDROITE = 13,
            POLAR = 11,
            Flipper = 15;
    }

    
    constexpr int 
        NEOPIXEL = 47,
        BUZZER = 37;

}

#define QUALITY 14 // quality of the current measurement of the lidar
#define SPEED_MOTOR_LIDAR 120 // speed of the motor of the lidar (max 255)
#define RPLIDAR_MOTOR 8 // The PWM pin for control the speed of RPLIDAR's motor.
#define MAX_DISTANCE_LIDAR 3500 // max distance of the lidar in mm
#define DIST_OBSTACLE 350 // distance of the obstacle in mm
#define TIME_TO_CHANGE 0.1

// Related to servos
#define SERVO_FREQ_HZ 50
// #define SERVO_Z_GAUCHE 1
// #define SERVO_PINCE_DROITE 2
// #define SERVO_PINCE_GAUCHE 3
// #define SERVO_MOVE_PINCE 4

#define SERVO_PANNEAU_GAUCHE 0
#define SERVO_PANNEAU_DROITE 15



//Related to Steppers
#define MOUVEMENT_SPEED 4000.0
#define MOUVEMENT_ACCELERATION 2000.0