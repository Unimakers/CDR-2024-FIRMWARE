#include <Arduino.h>
#include <RPLidar.h>
#include <HardwareSerial.h>
#include <AccelStepper.h>
#include <UniBoardDef.h>
#include <chrono>
#include <time.h>
#include <chrono.h>

// You need to create an driver instance 
RPLidar lidar;
 
// Steppers left and right
AccelStepper NEMAL(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper NEMAR(AccelStepper::DRIVER, STEP2, DIR2);

HardwareSerial mySerial (1);

//create a file named STRUCT_LIDAR_MESURE to ad the point mesure by the lidar
typedef struct {
    float distance = 0;
    float angle = 0;
    //bool startBit;
    float quality = 0;
}STRUCT_LIDAR_MESURE;



STRUCT_LIDAR_MESURE mesure;

int status_obstacle = 0;



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
        status_obstacle = 1;
    } else {
        digitalWrite(47, LOW);
        status_obstacle = 0;
    }
}


int ANGLE_IN_RANGE() {
    if ((mesure.angle >= 160 && mesure.angle <= 200) || (mesure.angle >= 340 || mesure.angle <= 20)) {
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

void clignoter() {
    int i =0;
    for(i = 0; i < 5; i++){
    led(1);
    delay(50);
    led(0);
    delay(50);
    }
    
}


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
        //Serial.println("check connection...");
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
    pinMode(47, OUTPUT);
    digitalWrite(47, HIGH);
    delay(3000);
    digitalWrite(47, LOW);
    lidar.begin(mySerial);
    Serial.begin(115200);
    // set pin modes
    pinMode(RPLIDAR_MOTOR, OUTPUT);
    analogWrite(RPLIDAR_MOTOR, SPEED_MOTOR_LIDAR); //start the rplidar motor
    Serial.println("Begin code");
    delay(2000);

    // Bind steppers
    pinMode(TIR, INPUT_PULLUP);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, HIGH);

    NEMAL.setMaxSpeed(4000.0);
    NEMAL.setAcceleration(2000.0);
    NEMAR.setMaxSpeed(4000.0);
    NEMAR.setAcceleration(2000.0);

    Serial.println("Waiting for button press");
    while (digitalRead(TIR) == 1);

    NEMAL.moveTo(1000000);
    NEMAR.moveTo(-1000000);
    digitalWrite(EN, LOW);
    Serial.println("Steppers start");
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
    }

void loop() {

    while (status_obstacle == 0) {
        NEMAL.run();
        NEMAR.run();  
    }
}
