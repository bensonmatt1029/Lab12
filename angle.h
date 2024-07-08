/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Daniel Malasky
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   // Constructors
   Angle() : radians(0.0) {}
   Angle(const Angle& rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians((2 * M_PI)* (degrees / 360)) {}

   // Getters
   double getDegrees() const { return (radians / (2 * M_PI)) * 360; }
   double getRadians() const { return radians; }

   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dy = cos a
   // dx = sin a
   double getDx()   const { return sin(radians); }
   double getDy()   const { return cos(radians); }
   bool   isRight() const { return radians > 0.0 && radians <= M_PI_2; }
   bool   isLeft()  const { return radians >= (M_PI + M_PI_2) && radians < 2 * M_PI; }


   // Setters
   void setDegrees(double degrees);
   void setRadians(double radians);
   void setUp() { this->radians = 0.0; }
   void setDown() { this->radians = M_PI; }
   void setRight() { this->radians = M_PI_2; }
   void setLeft() { this->radians = M_PI + M_PI_2; }
   void reverse() { this->radians += M_PI; }
   Angle& add(double delta);

   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   void setDxDy(double dx, double dy) { this->radians = normalize(atan(dx / dy)); }
   Angle operator+(double degrees) const { return Angle(); }

private:

   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}