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

    
}


#define LIDAR_TX 18
#define LIDAR_RX 17
#define LIDAR_PWM 3

#define SDA 5
#define SCL 4

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
