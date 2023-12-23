#include <Arduino.h>
#include <RPLidar.h>
#include <HardwareSerial.h>
#include <AccelStepper.h>
#include <UniBoardDef.h>
#include <chrono>
#include <time.h>
#include <chrono.h>
#include <motion.h>
#include <ihm.h>



// d8888b. db    db db       .d8b.  d8b   db      d8888b. d88888b      d8888b. d8888b. d88888b d888888b  .d8b.   d888b  d8b   db d88888b 
// 88  `8D `8b  d8' 88      d8' `8b 888o  88      88  `8D 88'          88  `8D 88  `8D 88'     `~~88~~' d8' `8b 88' Y8b 888o  88 88'     
// 88   88  `8bd8'  88      88ooo88 88V8o 88      88   88 88ooooo      88oooY' 88oobY' 88ooooo    88    88ooo88 88      88V8o 88 88ooooo 
// 88   88    88    88      88~~~88 88 V8o88      88   88 88~~~~~      88~~~b. 88`8b   88~~~~~    88    88~~~88 88  ooo 88 V8o88 88~~~~~ 
// 88  .8D    88    88booo. 88   88 88  V888      88  .8D 88.          88   8D 88 `88. 88.        88    88   88 88. ~8~ 88  V888 88.     
// Y8888D'    YP    Y88888P YP   YP VP   V8P      Y8888D' Y88888P      Y8888P' 88   YD Y88888P    YP    YP   YP  Y888P  VP   V8P Y88888P 
                                                                                                                                      




HardwareSerial mySerial (1);


// You need to create an driver instance 
RPLidar lidar;
 
// Steppers left and right
AccelStepper NEMAL(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper NEMAR(AccelStepper::DRIVER, STEP2, DIR2);

//intialise the wrapper
Motion Robot(NEMAL,NEMAR, EN);

//Initialise Human machine interface
IHM Physical;

//create a file named STRUCT_LIDAR_MESURE to ad the point mesure by the lidar
typedef struct {
    float distance = 0;
    float angle = 0;
    //bool startBit;
    float quality = 0;
}STRUCT_LIDAR_MESURE;

STRUCT_LIDAR_MESURE mesure;

bool status_obstacle = false;




void reset_point() {
    mesure.distance = 0;
    mesure.angle = 0;
    mesure.quality = 0;
}

//allow tp turn on the led 
//call with 1 to turn on and 0 to turn off
void led(int statue) {
    if (statue == 1) {
        digitalWrite(47, HIGH);
        status_obstacle = true;
    } else {
        digitalWrite(47, LOW);
        status_obstacle = false;
    }
}


int ANGLE_IN_RANGE() {
    if ((mesure.angle >= 250 && mesure.angle <= 290) || (mesure.angle >= 70 || mesure.angle <= 110)) {
        return true;
    }
    return false;
}

void obstacle() {
    if (mesure.distance < DIST_OBSTACLE && mesure.distance > 50) {
      if(check_chrono()==0){
        start_chrono();
      }else if(check_chrono()<TIME_TO_CHANGE) {
        led(1);
        reinitialise_chrono();
        start_chrono();
      }else {
        reinitialise_chrono();
        start_chrono();
        led(0);
      }
    }else if(check_chrono()>TIME_TO_CHANGE){
        led(0);
        stop_chrono();
        reinitialise_chrono();
    }
}

// bool check_target(int dist_target, int angle_to_check) {
//     if (mesure.distance < dist_target + 100 && mesure.distance > dist_target - 100) {
//         if (mesure.angle < angle_to_check + 10 && mesure.angle > angle_to_check - 10) {
//             led(1);
//             //delay(50);
//             return true ;
//         }
//     }
//     led(0);
//     return false;
// }



void get_point_lidar() {
    if (IS_OK(lidar.waitPoint())) { //check if the lidar is connected
      mesure.angle = lidar.getCurrentPoint().angle; //anglue value in degree
      if(ANGLE_IN_RANGE()){
        mesure.distance = lidar.getCurrentPoint().distance; //distance value in mm unit
        mesure.quality = lidar.getCurrentPoint().quality;
        if(mesure.quality > QUALITY){
          obstacle();
        }else{
          reset_point();
        }
        }
    } else { //if the lidar is not connected
        analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor

        rplidar_response_device_info_t info;
        if (IS_OK(lidar.getDeviceInfo(info, 100))) { //check if the lidar is connected
            // detected...
            lidar.startScan();
            // start motor rotating at max allowed speed
            analogWrite(RPLIDAR_MOTOR, SPEED_MOTOR_LIDAR);
            delay(1000);
        }
    }
}

void LidarTask(void *pvParameters)
{
	for (;;)
	{
        get_point_lidar();
        
    }
}

void print_mesure() {
    Serial.print(">lidar:");
    Serial.print(mesure.distance * cos(mesure.angle * DEG_TO_RAD));
    Serial.print(":");
    Serial.print(mesure.distance * sin(mesure.angle * DEG_TO_RAD));
    Serial.print(":");
    Serial.println("|xy");
}

void setup() {
    // bind the RPLIDAR driver to the arduino hardware serial

    delay(5000);
    lidar.begin(mySerial);
    Serial.begin(115200);

    pinMode(RPLIDAR_MOTOR, OUTPUT);
    analogWrite(RPLIDAR_MOTOR, SPEED_MOTOR_LIDAR); //start the rplidar motor

    Serial.println("Begin code");
    delay(2000);

    // inialise steppers
    Robot.SetMaxAcceleration(2000.0);
    Robot.SetSpeed(4000.0);

    Serial.println("Waiting for button press");
    while (Physical.GetTirette());
    Robot.MoveLine(15000);

    Robot.Enable();
    Serial.println("Steppers start");
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

void loop() {
    if(Robot.TargetReached()){
        Robot.Disable();
    }else{
        if(!status_obstacle) {
            Robot.Run();
        }else{
            Robot.Stop();
            while (status_obstacle) // attention, un while loop est bloquant, donc on peux faire autrement c'est mieux, peux etre des varibales d'état
            {
                Robot.Run();
            }
            Robot.Resume(); // resume la tache en cours
        }
    }
}
