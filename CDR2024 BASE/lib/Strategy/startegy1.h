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

    // go to jardiniere
    case 18:
      if(Robot.Go_to(762,225)==true){
        BARIL.Half();
        state++;
      }
      //Robot.SetCurrentCoords(Robot.CurrentCords.x,85,-90);

    break;
    case 19:
        if(Robot.Go_to(762,65)==true){
        BARIL.Half();
        state++;
        }
      
    break;
    case 20:
    //   Robot.MoveLine(-250);
        state++;
    break;
    case 21:
    //   Robot.SetCurrentCoords(200,550,0);
    //   Robot.Turn(90);
      state++;

    break;
    case 22:
      //Robot.MoveLine(200);
      //Robot.SetCurrentCoords(85,Robot.CurrentCords.y,180);
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
    case 32:
      PinceGauche.ungrab();
      PinceDroite.ungrab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 33:

        Robot.MoveLine(-200);
        Robot.SetCurrentCoords(Robot.CurrentCords.x, 285, Robot.CurrentCords.o);
        state++;
    break;

    case 34:

        if(Robot.Go_to(300,250)==true){
            PinceGauche.turnIn();
            PinceDroite.turnIn();
            state++;

        }else{
            BARIL.Half();
            PinceGauche.lift();
            PinceDroite.lift();
        }

    break;
    case 35:

    if(Robot.Go_to(80,250)==true){
        state++;
    }else{
        Robot.SetMaxAcceleration(2000);
        Robot.SetSpeed(2000);
        PinceGauche.turnIn();
        PinceDroite.turnIn();
        ServoCooldown.SetTimer(500);
        ServoCooldown.StartTimer();
    }
    break;

    case 36:
        Robot.MoveLine(-250);
        Robot.SetCurrentCoords(250+85,Robot.CurrentCords.y, 180);
        Robot.SetMaxAcceleration(MOUVEMENT_SPEED);
        Robot.SetSpeed(MOUVEMENT_ACCELERATION);
        state++;

    case 37:
        PinceGauche.drop();
        PinceDroite.drop();
        ServoCooldown.SetTimer(500);
        ServoCooldown.StartTimer();
        state++;
    break;

    case 38:
      PinceGauche.grab();
      PinceDroite.grab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;
    case 39:
      PinceGauche.lift();
      PinceDroite.lift();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;

    case 40:
      PinceGauche.turnOut();
      PinceDroite.turnOut();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;

    case 41:
      PinceGauche.drop();
      PinceDroite.drop();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;

    case 42:
      PinceGauche.ungrab();
      PinceDroite.ungrab();
      ServoCooldown.SetTimer(500);
      ServoCooldown.StartTimer();
      state++;
    break;

    case 43:
        Robot.MoveLine(-400);
        Robot.SetCurrentCoords(Robot.CurrentCords.x+400,Robot.CurrentCords.y, 180);
        state++;
    break;

    case 44:
        if(Robot.Go_to(250,2000)){
            PinceGauche.lift();
            PinceDroite.lift();
            state++;
        }
    break;

    case 45:
        Robot.MoveLine(-200);
        Robot.SetCurrentCoords(Robot.CurrentCords.x,2000-250,90);
        state++;
        break;

    case 46:
        if(Robot.Go_to(250,1750)){
            state++;
        }
    break;

    case 47:
        Robot.MoveLine(-200);
        Robot.SetCurrentCoords(135,1750,0);
        state++;

    break;

    case 48:
        if(Robot.Go_to(1250,1800)){
            state++;
        }else{
            PinceDroite.flipout();
        }
    break;


    default:
      
      break;
    }
  }


void YellowStrategy()
{


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