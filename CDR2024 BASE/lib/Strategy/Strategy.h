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

void BlueStrategy()
{
  static int state = 0;
  switch (state)
  {
    case 0:

      if(Robot.Go_to(1000,350)==true){
        state++;
        PinceDroite.turnOut();
        PinceGauche.turnOut();
        PinceDroite.ungrab();
        PinceGauche.ungrab();
      }
        Serial.println("Etape1");

      break;
    
    case 1:

      if(Robot.Go_to(1000,520)==true){
        state++;
      }else{
        PinceDroite.drop();
        PinceGauche.drop();
      }
      break;
    case 2:
      PinceGauche.grab();
      PinceDroite.grab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 3:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 4:
      PinceGauche.turnIn();
      PinceDroite.turnIn();
      ServoCooldown.SetTimer(1000);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 5:
      PinceGauche.drop();
      PinceDroite.drop();
      ServoCooldown.SetTimer(1000);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 6:
      PinceGauche.ungrab();
      PinceDroite.ungrab();
      ServoCooldown.SetTimer(1000);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 7:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(1000);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 8:
      if(Robot.Go_to(1000,600)==true){
        PinceGauche.drop();
        PinceDroite.drop();
        state++;
      }else{
        BARIL.Half();
        PinceGauche.turnOut();
        PinceDroite.turnOut();
        ServoCooldown.SetTimer(500);
        ServoCooldown.StartTimer();
      }
      break;
    case 9: 
      PinceGauche.grab();
      PinceDroite.grab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 10:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 11:
      PinceGauche.turnIn();
      PinceDroite.turnIn();
      ServoCooldown.SetTimer(1000);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 12:
      PinceGauche.drop();
      PinceDroite.drop();
      ServoCooldown.SetTimer(1000);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 13:
      PinceGauche.ungrab();
      PinceDroite.ungrab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 14:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 15:
      if(Robot.Go_to(1000,700)==true){
        PinceGauche.drop();
        PinceDroite.drop();
        state++;
      }else{
        PinceGauche.turnOut();
        PinceDroite.turnOut();
        ServoCooldown.SetTimer(500);
        ServoCooldown.StartTimer();
      }
      break;
    case 16: 
      PinceGauche.grab();
      PinceDroite.grab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
      break;
    case 17: 
      PinceGauche.lift();
      PinceDroite.lift();
      state++;
      break;
    case 18:
      if(Robot.Go_to(250,300)==true){
        BARIL.Half();
        state++;
      }
    break;
    case 19:
      if(Robot.Go_to(200,800)==true){
        state++;
      }
      
    break;
    case 20:
      Robot.MoveLine(-250);
      state++;
    break;
    case 21:
      Robot.SetCurrentCoords(200,550,0);
      Robot.Turn(90);
      state++;

    break;
    case 22:
      Robot.MoveLine(200);
      Robot.SetCurrentCoords(85,Robot.CurrentCords.y,Robot.CurrentCords.o);
      state++;
    break;
    case 23:
      PinceGauche.dropPlanters();
      PinceDroite.dropPlanters();

      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 24:
      PinceGauche.ungrab();
      PinceDroite.ungrab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 25:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 26:
      PinceGauche.turnIn();
      PinceDroite.turnIn();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 27:
      PinceGauche.drop();
      PinceDroite.drop();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 28:
      PinceGauche.grab();
      PinceDroite.grab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 29:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 30:
      PinceGauche.turnOut();
      PinceDroite.turnOut();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 31:
      PinceGauche.dropPlanters();
      PinceDroite.dropPlanters();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    default:
      
      break;
    }
  }

  void YellowStrategy()
  {
    static int state = 0;
    switch (state)
    {
    case 0:
      PinceDroite.flipout();
      Robot.MoveLine(1000);
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