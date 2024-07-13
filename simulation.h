/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"      // for GROUND
#include "howitzer.h"    // for HOWITZER


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) :
      ground(posUpperRight) 
   {
      howitzer.generatePosition(posUpperRight);
   }

   void display();

private:
   Ground ground;
   Howitzer howitzer;

};
