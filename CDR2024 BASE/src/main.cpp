//community libraries
#include <Arduino.h>
#include <RPLidar.h>
#include <HardwareSerial.h>
#include <AccelStepper.h>
#include <Adafruit_PWMServoDriver.h>

//Board Carateritics
#include <UniBoardDef.h>

#include <chrono>
#include <time.h>
#include <chrono.h>

//custom libraries
#include <Strategy.h>
#include <ihm.h>
#include <ChadServo.h>
#include <SoftTimer.h>
#include "Debug.h"

//custom wrappers
#include <BNO08X.h>
//#include <UdpWrapper.h>
#include <motion.h>
#include "Baril.h"

// macro for debug
#define DEBUG 1

// d8888b. db    db db       .d8b.  d8b   db      d8888b. d88888b      d8888b. d8888b. d88888b d888888b  .d8b.   d888b  d8b   db d88888b
// 88  `8D `8b  d8' 88      d8' `8b 888o  88      88  `8D 88'          88  `8D 88  `8D 88'     `~~88~~' d8' `8b 88' Y8b 888o  88 88'
// 88   88  `8bd8'  88      88ooo88 88V8o 88      88   88 88ooooo      88oooY' 88oobY' 88ooooo    88    88ooo88 88      88V8o 88 88ooooo
// 88   88    88    88      88~~~88 88 V8o88      88   88 88~~~~~      88~~~b. 88`8b   88~~~~~    88    88~~~88 88  ooo 88 V8o88 88~~~~~
// 88  .8D    88    88booo. 88   88 88  V888      88  .8D 88.          88   8D 88 `88. 88.        88    88   88 88. ~8~ 88  V888 88.
// Y8888D'    YP    Y88888P YP   YP VP   V8P      Y8888D' Y88888P      Y8888P' 88   YD Y88888P    YP    YP   YP  Y888P  VP   V8P Y88888P

// ██    ██ ██ ███████ ██ ████████ ███████ ██████      ██████  ██    ██     ██      ███████     ██████   █████  ████████
// ██    ██ ██ ██      ██    ██    ██      ██   ██     ██   ██  ██  ██      ██      ██          ██   ██ ██   ██    ██
// ██    ██ ██ ███████ ██    ██    █████   ██   ██     ██████    ████       ██      █████       ██████  ███████    ██
//  ██  ██  ██      ██ ██    ██    ██      ██   ██     ██   ██    ██        ██      ██          ██   ██ ██   ██    ██
//   ████   ██ ███████ ██    ██    ███████ ██████      ██████     ██        ███████ ███████     ██   ██ ██   ██    ██

HardwareSerial mySerial(1);

// You need to create an driver instance
RPLidar lidar;
// Initialise Human machine interface
IHM Physical;

// create a file named STRUCT_LIDAR_MESURE to ad the point mesure by the lidar
typedef struct
{
  float distance = 0;
  float angle = 0;
  // bool startBit;
  float quality = 0;
} STRUCT_LIDAR_MESURE;

STRUCT_LIDAR_MESURE mesure;


bool status_obstacle = false;
bool old_status_obstacle = false;
bool Armed = true;

// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// unsigned long previous_millis_servo = 0;

// TO-DO
/*
void debug() {
	if (DEBUG) {
		Serial.println()
	}
}
*/

void reset_point()
{
  mesure.distance = 0;
  mesure.angle = 0;
  mesure.quality = 0;
}

bool ANGLE_IN_RANGE()
{
  if ((mesure.angle >= 250 && mesure.angle <= 290) || (mesure.angle >= 70 && mesure.angle <= 110))
  {
    return true;
  }
  return false;
}

//A square hitbox function
bool ANGLE_IN_RANGE_SQUARE(){
  if (mesure.angle >= 70 && mesure.angle <= 110)
  {
    if (mesure.distance < DIST_OBSTACLE/sin(mesure.angle))
    {
      return true;
    }
  }
  return false;
}

void obstacle()
{
  if (mesure.distance < DIST_OBSTACLE && mesure.distance > 10)
  {
    if (check_chrono() == 0)
    {
      start_chrono();
    }
    else if (check_chrono() < TIME_TO_CHANGE)
    {
      status_obstacle = true;
      reinitialise_chrono();
      start_chrono();
    }
    else
    {
      reinitialise_chrono();
      start_chrono();
      status_obstacle = false;
    }
  }
  else if (check_chrono() > TIME_TO_CHANGE)
  {
    status_obstacle = false;
    stop_chrono();
    reinitialise_chrono();
  }
}


void get_point_lidar()
{
  if (IS_OK(lidar.waitPoint()))
  {                                               // check if the lidar is connected
    mesure.angle = lidar.getCurrentPoint().angle; // anglue value in degree
    if (ANGLE_IN_RANGE())
    {
      mesure.distance = lidar.getCurrentPoint().distance; // distance value in mm unit
      mesure.quality = lidar.getCurrentPoint().quality;
      if (mesure.quality > QUALITY)
      {
        obstacle();
      }
      else
      {
        reset_point();
      }
    }
  }
  else
  {                                // if the lidar is not connected
    analogWrite(RPLIDAR_MOTOR, 0); // stop the rplidar motor

    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100)))
    { // check if the lidar is connected
      // detected...
      lidar.startScan();
      // start motor rotating at max allowed speed
      analogWrite(RPLIDAR_MOTOR, SPEED_MOTOR_LIDAR);
      delay(1000);
    }
  }
}
// pour commit
void LidarTask(void *pvParameters)
{
  for (;;)
  {
    get_point_lidar();
    //ServoCooldown.updateTimer(); // temporairement ici car veux m'assurer qu'elle est run
  }
}


void setup()
{
  // bind the RPLIDAR driver to the arduino hardware serial
  Strat = YELLOW;
  lidar.begin(mySerial,PIN::Lidar::LIDAR_RX,PIN::Lidar::LIDAR_TX);
  Serial.begin(115200);

  Wire.begin(PIN::I2C::SDA, PIN::I2C::SCL);

  scan_i2c();
  // BNO initialisation
  //BNO_init();
  // Wifi Udp Initialistation
  //UDP_init();

  // Servos
  pwm.begin();
  pwm.setOscillatorFrequency(25000000); // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/examples/servo/servo.ino#L49
  pwm.setPWMFreq(SERVO_FREQ_HZ);


  pinMode(RPLIDAR_MOTOR, OUTPUT);
  analogWrite(RPLIDAR_MOTOR, SPEED_MOTOR_LIDAR); // start the rplidar motor

  // send Ok Command over udp
  //UDPSendInfo(200);

  Serial.println("Begin code");
  delay(2000);

  // inialise steppers
  Robot.SetMaxAcceleration(1000.0);
  Robot.SetSpeed(2500.0);


  //Attach lidar to core 0
  xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);

  Serial.println("Waiting for insert tirrette");

  while (!Physical.GetButton(1))
  {
  }

  Serial.println("Waiting for remove tirrette");
  delay(1000); // wait for stable connection
  while (Physical.GetButton(1))
  {
  }

  delay(1000);
  Robot.Enable();

  //Robot.Disable();
  Serial.println("Steppers start");


	pinMode(PIN::Nappe::NAPPE1, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE2, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE3, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE4, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE5, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE6, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE7, INPUT_PULLUP);
	pinMode(PIN::Nappe::NAPPE8, INPUT_PULLUP);
}

void HumanPeriphirals()
{

}

void ObstacleHandle()
{
  // maybe use a temp status, to prevent any problems because of the double core
  bool tmp_status = status_obstacle;
  // compare si il y a eu un changement d'etat, si oui, alors agir en fonction de l'état
  if (tmp_status != old_status_obstacle)
  {
    if (tmp_status)
    {
      Robot.Stop();
      // Serial.println("Obst, stopping");
    }
    else
    {
      Robot.Resume();
      // Serial.println("NO-Obst, resuming");
    }
    old_status_obstacle = tmp_status; // if the 2nd core changes status obstacle right before this command, it becomes bugged, thats why we use tmp_status
  }
}

void RobotPeriphirals()
{
  ObstacleHandle();
  if (!Robot.GetPendingStop())
  { // test if there is a obstacle stop in work, if so, then do check the strategy mouvement
    StrategyEvent();
  }
  Robot.Run();
  BARIL.Run();
}

void DisplayPeriphirals()
{
}

// try to make the program modular please
void loop()
{
	static bool test = true;

	if (test) {
		Robot.initCurrentCoords('B', 3);
		BARIL.Probe();
		test = false;
	}
	
  // HumanPeriphirals();  // comment or modular before match

  if (Armed)
  { // will only run if the robot is not manually disabled

    //RobotPeriphirals();

  }
}
