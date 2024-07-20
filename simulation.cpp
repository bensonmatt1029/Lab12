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


   // Draw the howitzer
   howitzer.draw(gout, 100.0);
   
   // Draw the ground
   ground.draw(gout);

   // Draw the projectile
   projectile.draw(gout);

   
   gout = Position(23000, 18000);  // set position of messages
   gout.setf(ios::fixed);          // for double precision
   gout.precision(1);

   // Show howitzer gun angle
   if (!projectile.isFlying())
   {
      gout << "Angle: " << howitzer.getElevation()
          << endl;
   }
   // Show projectile information
   else
   {
      // display the fuel, altitude, and speed
      gout << "Altitude: " << projectile.getAltitude()
           << endl;
      gout << "Speed: " << projectile.getSpeed()
           << endl;
      gout << "Distance: " << projectile.getFlightDistance()
           << endl;
      gout << "Hang Time: " << projectile.getCurrentTime() // *NOTE* right getter?
           << endl;
      gout << "Projectile pos: " << projectile.getPosition().getMetersX() << ' ' << projectile.getPosition().getMetersY()  // *NOTE* right getter?
           << endl;
      gout << "Target pos: " << ground.getTarget().getMetersX() << ' ' << ground.getTarget().getMetersY()  // *NOTE* right getter?
           << endl;
   }


   // TODO
   // display projectile trail.

}



void Simulator::update(const Interface* pUI)
{
   // TODO
   // moving the howitzer angle (left, right, up)
   // firing the projectile (space)
   // projectile trail


   // *NOTE*
   // check rotate speed
   // make it so it can't rotate in a whole circle.
   // Move gun to the right
   if (pUI->isRight())
   {
      //if (howitzer.getElevation().getRadians() <= M_PI_2)
      //{ 
      howitzer.rotate(.1);
      //} 
   }
   // Move gun to the left.
   if (pUI->isLeft())
   {
      //if (howitzer.getElevation().getRadians() >= (M_PI + M_PI_2))
      //{
      howitzer.rotate(-.1);
      //}
   }
   // Raise the gun to straight up.
   if (pUI->isUp())
   {
      if (howitzer.getElevation().getRadians() != 0.0)
      {
         howitzer.raise(0.01);
      }
   }
   // Lower the gun in either direction.
   if (pUI->isDown())
   {
      howitzer.raise(-0.01);
   }

   



   //projectile.fire(pUI);

}

// *NOTE*
// maybe don't need pUI
void Simulator::advance(const Interface* pUI)
{
   // TODO
   // check projectile collision with target and ground
   // can't fire until projectiles lands
   // reset game function?


   //*NOTE*
   // Not working at all.
   Velocity projectileSpeed;
   projectileSpeed.set(howitzer.getElevation().getRadians(), howitzer.getMuzzleVelocity());

   if (pUI->isSpace() && !projectile.isFlying())
   {
      projectile.fire(howitzer.getPosition(), 0.5, howitzer.getElevation(), howitzer.getMuzzleVelocity());
      projectile.advance(1.0);
      
   }
   if (projectile.isFlying())
   {
      // YOU SUNK MY BATTLESHIP
      if (projectile.getPosition().getPixelsX() >= ground.getTarget().getPixelsX() - 10.0 &&
         projectile.getPosition().getPixelsX() <= ground.getTarget().getPixelsX() + 10.0 &&
         projectile.getPosition().getPixelsY() >= ground.getTarget().getPixelsY() - 10.0 &&
         projectile.getPosition().getPixelsY() <= ground.getTarget().getPixelsY() + 10.0)
      {
         howitzer.generatePosition(posUpperRight);
         ground.reset(howitzer.getPosition());
         projectile.reset();
      }
      if (ground.getElevationMeters(projectile.getPosition()) < projectile.getPosition().getMetersY())
      {
         projectile.advance(1.0);
      }

      else
      {
         projectile.reset();
      } 
    
   }
   
   

}



