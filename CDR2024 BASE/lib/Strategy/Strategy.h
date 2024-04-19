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

PinceAscenseur PinceGauche(PIN::PinceGauche::Z,PIN::PinceGauche::DOIGTGAUCE,PIN::PinceGauche::DOIGTDROITE,PIN::PinceGauche::POLAR);
PinceAscenseur PinceDroite(PIN::PinceDroite::Z,PIN::PinceDroite::DOIGTGAUCHE,PIN::PinceDroite::DOIGTDROITE,PIN::PinceDroite::POLAR);



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

    PinceGauche.grab();
    PinceDroite.grab();

    PinceGauche.lift();
    PinceDroite.lift();

    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    state++;
    break;
  case 1:
    PinceGauche.turnIn();
    PinceDroite.turnIn();
   


    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    state++;
    break;
  case 2: 
    PinceGauche.ungrab();
    PinceDroite.ungrab();
   


    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    state++;
    break;
  case 3:
    PinceGauche.turnOut();
    PinceDroite.turnOut();
   


    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    state++;
    break;
  case 4:
    PinceGauche.drop();
    PinceDroite.drop();
   


    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
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
    if(Robot.Go_to(650,950)==true){
      state++;
      PinceGauche.ungrab();
      PinceDroite.ungrab();
      PinceGauche.drop();
      PinceDroite.drop();
      PinceGauche.turnOut();
      PinceDroite.turnOut();
      Serial.println("Etape1");
    }
    
    break;
  case 1 :
    PinceGauche.grab();
    PinceDroite.grab();
    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    Serial.println("Etape2");
    state++;

   break;
  case 2:
    PinceGauche.lift();
    PinceDroite.lift();
    PinceGauche.turnIn();
    PinceDroite.turnIn();
    ServoCooldown.SetTimer(1000);
    ServoCooldown.StartTimer();
    Serial.println("Etape3");
    state++;
    break;
  case 3 :
  if(Robot.Go_to(650,75)==true){
       state++;
     }
  break;
  case 4:
    PinceGauche.ungrab();
    PinceDroite.ungrab();
    state++;

  default:
    break;
  }
}



//setInitilisation
void initStrategy(){
  switch (Strat)
  {
  case YELLOW:
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
  case BLUE:
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