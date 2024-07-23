/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Daniel Malasky and Matt Benson
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

   // Show a negative angle when angled to the left
   Angle howitzerAngle(howitzer.getElevation());
   if (howitzer.getElevation().getDegrees() > 180.0)
   { 
      howitzerAngle = howitzer.getElevation().getDegrees() - 360;
   }

   // Show howitzer angle
   if (!projectile.isFlying())
   {
      gout << "Angle: " << howitzerAngle << endl;
   }
   // Show projectile information
   else
   {
      // Display the altitude, speed, distance, and hang time.
      gout << "Altitude: "  << projectile.getAltitude()       << endl;
      gout << "Speed: "     << projectile.getSpeed()          << endl;
      gout << "Distance: "  << projectile.getFlightDistance() << endl;
      gout << "Hang Time: " << projectile.getCurrentTime()    << endl;
   }
}

/**********************************************************
 * UPDATE
 * Update the simulator state for each frame
 **********************************************************/
void Simulator::update(const Interface* pUI)
{
   // Move gun to the right
   if (pUI->isRight())
   {
      howitzer.rotate(0.1);
   }
   // Move gun to the left.
   if (pUI->isLeft())
   {
      howitzer.rotate(-0.1);
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
}

/************************************************
 * GAMEPLAY
 * Handle the gameplay rules based on user input,
 * Projectile position and firing.
 ************************************************/
void Simulator::gameplay(const Interface* pUI)
{
   // Fire the gun
   if (pUI->isSpace() && !projectile.isFlying())
   {
      projectile.fire(howitzer.getPosition(), 0.5, howitzer.getElevation(), howitzer.getMuzzleVelocity());
      projectile.advance(1.0);
      
   }

   // Rules of the game
   if (projectile.isFlying())
   {
      // Check if projectile hit target.
      if (projectile.getPosition().getPixelsX() >= ground.getTarget().getPixelsX() - 10.0 &&
         projectile.getPosition().getPixelsX() <= ground.getTarget().getPixelsX() + 10.0 &&
         projectile.getPosition().getPixelsY() >= ground.getTarget().getPixelsY() - 10.0 &&
         projectile.getPosition().getPixelsY() <= ground.getTarget().getPixelsY() + 10.0)
      {
         howitzer.generatePosition(posUpperRight);
         ground.reset(howitzer.getPosition());
         projectile.reset();
      }
      // Check if projectile has not hit the ground
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



