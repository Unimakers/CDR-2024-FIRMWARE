#pragma once
#ifndef _STRATEGY_H
#define _STRATEGY_H
#endif


#include "BNO08X.h"
#include "UdpWrapper.h"
#include "SoftTimer.h"
#include "motion.h"
#include "ChadServo.h"


SoftTimer ServoCooldown;

Motion& Robot = Motion::instance();

typedef enum
{
  BLUE,
  YELLOW
} Strategy;

Strategy Strat = YELLOW;

void BlueStrategy()
{
  static int state = 0;
  switch (state)
  {
  case 0:
    //Robot.MoveLine(-1000);
    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    servo_z(1,0);
    servo_xy(2,80);
    servo_xy(3,30);
    state++;
    break;
  case 1:
    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    servo_xy(2,35);
    servo_xy(3,65);
    state++;
    break;
  case 2:
    //Robot.MoveLine(1000);
    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    servo_z(1,50);
    state++;
    break;
  default:
    state = 0;
    break;
  }
}

void YellowStrategy()
{
  static int state = 0;
  switch (state)
  {
  case 0:
    Robot.MoveLine(1000);
    state++;
    break;
  case 1:
    Robot.MoveLine(-1000);
    state++;
    break;
  default:
    break;
  }
}



//setInitilisation
void initStrategy(){
  switch (Strat)
  {
  case BLUE:

    break;
  case YELLOW:
    /* code */
    break;
  
  default:
    break;
  }
}


void StrategyEvent()
{
  if (Robot.TargetReached() && ServoCooldown.IsEnded())
  {
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
}