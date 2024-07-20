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
#include "projectile.h"  // for PROJECTILE
#include "uiInteract.h"  // for INTERFACE

using namespace std;


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
      ground.reset(howitzer.getPosition());
      
   }

   // display stuff on the screen
   void display();

   // update the simulator for each frame
   // input
   void update(const Interface* pUI);

   // handle gameplay rules
   // advance
   void advance(const Interface* pUI);

private:
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;

};
