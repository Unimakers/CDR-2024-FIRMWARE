#include <Arduino.h>
#include <RPLidar.h>
#include <HardwareSerial.h>
#include <AccelStepper.h>
#include <UniBoardDef.h>
//

#define RXD1 17
#define TXD1 18
#define SER_BUF_SIZE 1024
#define QUALITY 8 // quality of the current measurement of the lidar
#define SPEED_MOTOR_LIDAR 120 // speed of the motor of the lidar (max 255)
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
#define MAX_DISTANCE_LIDAR 3500 // max distance of the lidar in mm
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define dist_obstacle 300 // distance of the obstacle in mm

// You need to create an driver instance 
RPLidar lidar;

HardwareSerial mySerial (1);



//create a file named STRUCT_LIDAR_MESURE to ad the point mesure by the lidar
typedef struct {
  float distance = 0;
  float angle = 0;
  //bool startBit;
  float quality = 0;
} STRUCT_LIDAR_MESURE;


void reset_point(){
  mesure.distance = 0;
  mesure.angle = 0;
  mesure.quality = 0;
}

void led(int statue){
  if(statue == 1){
    digitalWrite(47, HIGH);
  }else{
    digitalWrite(47, LOW);
  }
}

STRUCT_LIDAR_MESURE mesure ;

bool obstacle(){
  if(((mesure.distance < dist_obstacle) && (mesure.distance >50))){
    if((mesure.angle <200) && (mesure.angle > 160)){
      led(1);
      delay(50);
      return true; 
    }
    if((mesure.angle > 340) || (mesure.angle < 20)){
      led(1);
      delay(50);
      return true ;
    }
    return false ;
  }
  led(0);
  return false;
  
}

bool check_target(int dist_target, int angle_to_check){
  if((mesure.distance < dist_target + 100) && (mesure.distance > dist_target - 100)){
    if((mesure.angle < angle_to_check + 10) && (mesure.angle > angle_to_check - 10)){
      led(1);
      delay(50);
      return true ;
    }

  }
  led(0);

}

void get_point_lidar(){
  if (IS_OK(lidar.waitPoint())) { //check if the lidar is connected
    mesure.distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    mesure.quality = lidar.getCurrentPoint().quality; 
    if((mesure.distance < MAX_DISTANCE_LIDAR) && (mesure.quality > QUALITY)){
        mesure.angle = lidar.getCurrentPoint().angle; //anglue value in degree
        obstacle();
        }else {
          reset_point();
        }

  }else  {//if the lidar is not connected
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


void print_mesure(){
  Serial.print(">lidar:");
  Serial.print(mesure.distance * cos(mesure.angle*DEG_TO_RAD));
  Serial.print(":");
  Serial.print(mesure.distance * sin(mesure.angle*DEG_TO_RAD));
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
}


void loop() {

  get_point_lidar();
 // print_mesure();

}
