#pragma once
#ifndef _STRATEGY_H
#define _STRATEGY_H
#endif

#include "BNO08X.h"
#include "UdpWrapper.h"
#include "SoftTimer.h"
#include "motion.h"
#include "ChadServo.h"
#include "UniBoardDefV4.h"


SoftTimer ServoCooldown;

Motion& Robot = Motion::instance();
Baril& BARIL = Baril::instance();

PinceAscenseur PinceGauche(PIN::PinceGauche::Z,PIN::PinceGauche::DOIGTGAUCE,PIN::PinceGauche::DOIGTDROITE,PIN::PinceGauche::POLAR,PIN::PinceGauche::Flipper);
PinceAscenseur PinceDroite(PIN::PinceDroite::Z,PIN::PinceDroite::DOIGTGAUCHE,PIN::PinceDroite::DOIGTDROITE,PIN::PinceDroite::POLAR,PIN::PinceDroite::Flipper);

typedef enum
{
  BLUE,
  YELLOW
} Strategy;

Strategy Strat = YELLOW;

void YellowStrategy()
{
  static int state = 0;
  switch (state)
  { 
    case 0: 
      Robot.SetCurrentCoords(2750,1750,180);
      PinceGauche.flipout();
      state++;
      break;
    case 1:
      if(Robot.Go_to(2000,1750)){
        state++;
      }
    break;
    case 2:
     PinceGauche.flipin();
      if(Robot.Go_to(2750,250)){
        state++;
      }
      Serial.printf("L'angle : %f",Robot.CurrentCords.o);
    break;


    default:

      break;
    
  }

  }

  void BlueStrategy()
  {
    static int state = 0;
    switch (state)
    {

      case 0: 
        Robot.SetCurrentCoords(250,1750,0);
        PinceDroite.flipout();
        state++;
        break;
      case 1:
        if(Robot.Go_to(1000,1750)){
          state++;
        }
      break;
      case 2:
      PinceDroite.flipin();
        if(Robot.Go_to(250,250)){
          state++;
        }
      break;
      
      
      default:

      break;
    

  }
}



//setInitilisation
void initStrategy(){
  switch (Strat)
  {
  case YELLOW:

    
    


    break;
    
  case BLUE:
    Robot.SetCurrentCoords(250,250,0);
    Robot.MoveLine(-200);
    while (!Robot.TargetReached())
    {
      Robot.Run();
    }
    Robot.MoveLine(116);
    while (!Robot.TargetReached())
    {
      Robot.Run();
    }
    Robot.Turn(-90);
    while (!Robot.TargetReached())
    {
      Robot.Run();
    }
    Robot.MoveLine(-250);
    while (!Robot.TargetReached())
    {
      Robot.Run();
    }
    Robot.MoveLine(116);
    while (!Robot.TargetReached())
    {
      Robot.Run();
    }
    break;
  
  default:
    break;
  }
}


void StrategyEvent()
{
  if (Robot.TargetReached() && ServoCooldown.IsEnded() && BARIL.TargetReached())
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