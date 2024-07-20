/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Daniel Malasky
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION


/**********************************************************
 * DISPLAY
 * Draw on the screen
**********************************************************/
void Simulator::display()
{
   ogstream gout;

   // Draw the ground
   ground.draw(gout);

   // Draw the howitzer
   howitzer.draw(gout, 10.0);

   // Draw the projectile flight path
   projectile.draw(gout);
   
   // TODO
   // status messages

}

void Simulator::update(const Interface* pUI)
{
   // TODO
   // moving the howitzer angle (left, right, up)
   // firing the projectile (space)
   // projectile trail


   //projectile.fire(howitzer.getPosition(), projectile.getCurrentTime(), howitzer.set(pUI);

}

void Simulator::gameplay(const Interface* pUI)
{
   // TODO
   // check projectile collision with target and ground
   // can't fire until projectiles lands
   // reset game function?


}



