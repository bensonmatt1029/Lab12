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
#include "acceleration.h"
#include "uiDraw.h"
using namespace std;

/***********************************************************************
 * FIRE
 * Fires the projectile taking position, time, angle, and velocity.
 ************************************************************************/
void Projectile::fire(const Position& posHowitzer, double simulationTime,
   const Angle& elevation, double muzzleVelocity)
{
   reset();

   PositionVelocityTime pvt;
   pvt.pos = posHowitzer;
   pvt.t = simulationTime;
   pvt.v.set(elevation, muzzleVelocity);
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
   double newVelocityX = lastState.v.getDX() + 
      dragAccelerationX * simulationTime;
   double newPositionX = lastState.pos.getMetersX() + lastState.v.getDX() * 
      simulationTime + 0.5 * dragAccelerationX * simulationTime * simulationTime;
   newState.v.addDX(newVelocityX);
   newState.pos.addMetersX(newPositionX);

   // Update vertical position and velocity
   double newVelocityY = lastState.v.getDY() + 
      (GRAVITY - dragAccelerationY) * simulationTime;
   double newPositionY = lastState.pos.getMetersY() + lastState.v.getDY() * 
      simulationTime + 0.5 * (GRAVITY - dragAccelerationY) * simulationTime * simulationTime;
   newState.pos.addMetersY(newPositionY);
   newState.v.addDY(newVelocityY);

   // Add the new state to the flight path
   flightPath.push_back(newState);
}