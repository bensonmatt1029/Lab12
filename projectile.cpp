/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Matt Benson
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#include "projectile.h"
#include "angle.h"
#include "uiDraw.h"
using namespace std;


/***********************************************************************
 * GET ALTITUDE
 * Gets the current altitude of the projectile.
 ************************************************************************/
double Projectile::getAltitude() const
{
   if (!flightPath.empty())
      return flightPath.back().pos.getMetersY();
   return 0.0;
}

/***********************************************************************
 * GET POSITION
 * Gets the current position of the projectile.
 ************************************************************************/
Position Projectile::getPosition() const
{
   if (!flightPath.empty())
      return flightPath.back().pos;
   return Position();
}

/***********************************************************************
 * GET FLIGHT DISTANCE
 * Gets the horizontal distance the projectile has traveled.
 ************************************************************************/
double Projectile::getFlightDistance() const
{
   if (!flightPath.empty())
      return flightPath.back().pos.getMetersX();
   return 0.0;
}

/***********************************************************************
 * GET SPEED
 * Gets the current speed of the projectile.
 ************************************************************************/
double Projectile::getSpeed() const
{
   if (!flightPath.empty())
      return flightPath.back().v.getSpeed();
   return 0.0;
}

/***********************************************************************
 * GET CURRENT TIME
 * Gets the current simulation time.
 ************************************************************************/
double Projectile::getCurrentTime() const
{
   if (!flightPath.empty())
      return flightPath.back().t;
   return 0.0;
}

/***********************************************************************
 * DRAW
 * Draws the projectile path
 ************************************************************************/
void Projectile::draw(ogstream& gout) const
{
   // Iterate over the flight path and draw each position
   for (const auto& pvt : flightPath)

   {  // Drawing the projectile at each position in the flight path
      gout.drawProjectile(pvt.pos); 
   }

   // Draw the current position of the projectile
   if (!flightPath.empty())

   {  // Drawing the projectile at the last position
      gout.drawProjectile(flightPath.back().pos); 
   }
}

/***********************************************************************
 * FIRE
 * Fires the projectile taking position, time, angle, and velocity.
 ************************************************************************/
void Projectile::fire(Position pos, double time, double howitzerAngle, Velocity vel) 
{
   // Reverse the velocity if the angle is negative
   if (howitzerAngle < 0)
   {
      vel.reverse();
   }

   PositionVelocityTime pvt;
   pvt.pos = pos;
   pvt.v = vel;
   pvt.t = time;
   flightPath.push_back(pvt);
}

/***********************************************************************
 * ADVANCE
 * Advances the projectile forward in time.
 ************************************************************************/
void Projectile::advance(double simulationTime)
{
   // If there are no projectiles in flight, do nothing
   if (flightPath.empty())
   {
      return;
   } 

   // Get the last state of the projectile
   PositionVelocityTime lastState = flightPath.back();

   // Constants
   double speed = lastState.v.getSpeed();
   const double dragCoefficient = dragFromMach(speed / 
      speedSoundFromAltitude(lastState.pos.getMetersY()));
   const double airDensity = densityFromAltitude(lastState.pos.getMetersY());
   const double gravity = gravityFromAltitude(lastState.pos.getMetersY());

   // Calculate the drag force
   double dragForce = forceFromDrag(airDensity, dragCoefficient, 
      DEFAULT_PROJECTILE_RADIUS, speed);

   // Calculate the acceleration due to drag
   double accelerationDrag = 
      accelerationFromForce(dragForce, DEFAULT_PROJECTILE_WEIGHT);

   // Calculate the acceleration components due to drag
   double dragAccelerationX = (speed != 0) ? -accelerationDrag * 
      (lastState.v.getDX() / speed) : 0;
   double dragAccelerationY = (speed != 0) ? accelerationDrag * 
      (lastState.v.getDY() / speed) : 0;

   // Calculate the new time
   double newTime = lastState.t + simulationTime;

   // Calculate the new velocity
   PositionVelocityTime newState;
   newState.t = newTime;
   double newPositionX = lastState.pos.getMetersX() + lastState.v.getDX() * 
      simulationTime + 0.5 * dragAccelerationX * simulationTime * simulationTime;
   double newPositionY = lastState.pos.getMetersY() + lastState.v.getDY() *
      simulationTime + 0.5 * (gravity - dragAccelerationY) * simulationTime * simulationTime;
   newState.pos.addMetersX(newPositionX);
   newState.pos.addMetersY(newPositionY);

   // Update vertical position and velocity
   double newVelocityX = lastState.v.getDX() +
      dragAccelerationX * simulationTime;
   double newVelocityY = lastState.v.getDY() + 
      (gravity - dragAccelerationY) * simulationTime;
   newState.v.addDX(newVelocityX);
   newState.v.addDY(newVelocityY);

   // Add the new state to the flight path
   cout << flightPath.size() << " " << newState.pos.getMetersY() << endl;
   flightPath.push_back(newState);
   while (flightPath.size() > 10)
   {
      flightPath.pop_front();
   }

}