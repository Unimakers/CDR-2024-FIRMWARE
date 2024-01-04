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

// remove if you want to remove OTA
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


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

typedef enum
{
    BLUE,
    YELLOW
} Strategy;

Strategy Strat = BLUE;

const char* ssid = "Vanderputten tp link";
const char* password = "Putten01";

bool status_obstacle = false;
bool old_status_obstacle = false;
bool Armed = true;



//remove if you need to remove ota

void OTA_init(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Wow this has changed");
}

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

bool ANGLE_IN_RANGE() {
    if ((mesure.angle >= 250 && mesure.angle <= 290) || (mesure.angle >= 70 || mesure.angle <= 110)) {
        return true;
    }
    return false;
}

void obstacle() {
    if (mesure.distance < DIST_OBSTACLE && mesure.distance > 10) {
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

void BlueStrategy(){



}

void YellowStrategy(){



}

void StrategyEvent(){

  switch (Strat)
  {
  case BLUE:
        BlueStrategy();
    break;
  case YELLOW:
        YellowStrategy();
    break;
  
  default:
    break;
  }


}

void setup() {
    // bind the RPLIDAR driver to the arduino hardware serial
    OTA_init(); // remove if you need to remove ota
    delay(2000);

    lidar.begin(mySerial);
    Serial.begin(115200);

    pinMode(RPLIDAR_MOTOR, OUTPUT);
    analogWrite(RPLIDAR_MOTOR, SPEED_MOTOR_LIDAR); //start the rplidar motor

    Serial.println("Begin code");
    delay(2000);

    // inialise steppers
    Robot.SetMaxAcceleration(3000.0);
    Robot.SetSpeed(4000.0);

    Serial.println("Waiting for insert tirrette");
    while (!Physical.GetTirette()){
      ArduinoOTA.handle();
    }
    Serial.println("Waiting for remove tirrette");
    delay(1000);//wait for stable connection
    while (Physical.GetTirette()){
      ArduinoOTA.handle();
    }
    Robot.MoveLine(15000);

    Robot.Enable();
    Serial.println("Steppers start");
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

void HumanPeriphirals(){
  // if( Physical.GetButton(1) ){
  //   Robot.Disable();
  //   ArduinoOTA.handle();
  //   Armed = false;
  // }


}

void ObstacleHandle(){
  // maybe use a temp status, to prevent any problems because of the double core
  bool tmp_status = status_obstacle;
  //compare si il y a eu un changement d'etat, si oui, alors agir en fonction de l'état
  if(tmp_status != old_status_obstacle){
    if(tmp_status){
      Robot.Stop();
      //Serial.println("Obst, stopping");
    }else
    {
      Robot.Resume();
      //Serial.println("NO-Obst, resuming");
    }
    old_status_obstacle = tmp_status; //if the 2nd core changes status obstacle right before this command, it becomes bugged, thats why we use tmp_status
  }
}

void RobotPeriphirals(){  
  ObstacleHandle();
  if(!Robot.GetPendingStop()){
    
  }

  Robot.Run();
}

void DisplayPeriphirals(){



}


//try to make the program modular please
void loop() {
  HumanPeriphirals();  // comment or modular before match
  if(Armed){ //will only run if the robot is not manually disabled
    RobotPeriphirals();
  }

}