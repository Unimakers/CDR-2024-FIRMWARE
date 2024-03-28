#pragma once

namespace PIN{
    namespace Inputs{
        constexpr int 
            TIR = 8,
            btn1 = 1,
            btn2 = 2;
    }
    namespace Steppers{
        constexpr int
            STEP1 = 14,
            STEP2 = 12,
            STEP3 = 10,
            EN = 46,
            DIR1 = 13,
            DIR2 = 11,
            DIR3 = 9;
    } 
    namespace Lidar{
        constexpr int
             LIDAR_TX = 18,
             LIDAR_RX = 17,
             LIDAR_PWM = 3;
            
    }

    namespace I2C{
        constexpr int
            SDA = 5,
            SCL = 4;

    }
    namespace Nappe{
        constexpr int
            NAPPE1 = 21,
			NAPPE2 = 47,
			NAPPE3 = 48,
			NAPPE4 = 45,
			NAPPE5 = 38,
			NAPPE6 = 37,
			NAPPE7 = 36,
			NAPPE8 = 35;
    }

    
}


#define btn1 1
#define btn2 2

#define QUALITY 14 // quality of the current measurement of the lidar
#define SPEED_MOTOR_LIDAR 120 // speed of the motor of the lidar (max 255)
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
#define MAX_DISTANCE_LIDAR 3500 // max distance of the lidar in mm
#define DIST_OBSTACLE 350 // distance of the obstacle in mm
#define TIME_TO_CHANGE 0.1

// Related to servos
#define SERVO_FREQ_HZ 50
#define SERVO_HAUTEUR 1
#define SERVO_PINCE_DROITE 2
#define SERVO_PINCE_GAUCHE 3
#define SERVO_MOVE_PINCE 4
