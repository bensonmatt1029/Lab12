/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Daniel Malasky
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION

void Simulator::display()
{
   ogstream gout;

   ground.draw(gout);

   howitzer.draw(gout, 10.0);

}
