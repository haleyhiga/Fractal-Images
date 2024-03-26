#include "JuliaSet.h"

#include <iostream>
#include <cmath>


JuliaSet::JuliaSet( )
    : ComplexFractal(  ), mA( -0.650492 ), mB( -0.478235 ) {
        mMaxNumber = 255;
    }

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
    :  ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA( a ), mB( b )  { 

    }

JuliaSet::~JuliaSet( ) {} // destructor

double JuliaSet::getA( ) const {
    return mA;
}

double JuliaSet::getB( ) const {
    return mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {

    if (a <= 2 && a >= -2 && b <= 2 && b >= -2) { // inclusive
        mA = a;
        mB = b;
    }

}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
    //Calculate the next escape point after x0, y0 and store in x1, y1. 
    //Note that x1 and y1 are return by reference. This is the Julia set function x',y' = f(x,y).
    // x' = x*x - y*y + a
    // y' = 2*x*y + b

        x1 = (x0 * x0) - (y0 * y0) + mA;
        y1 = ( 2 * x0 * y0 ) + mB; 

}


int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
 
    double x = x0;
    double y = y0;
    int escapeCount = 0;

    while (escapeCount < getMaxNumber()) {
        if (x * x + y * y > 4.0) {
            break;
        }
        calculateNextPoint(x, y, x, y); // calculate next point in sequence
        escapeCount++;
    }

    return escapeCount;

}


int JuliaSet::calculateNumber( const int& row, const int& column ) const {
 
    double x, y;

    if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        return calculatePlaneEscapeCount(x, y);
    } else {
        return -1;
    }
}

JuliaSetFour::JuliaSetFour()
    : JuliaSet() {}

JuliaSetFour::~JuliaSetFour() {}

void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const {
   //x1 = x^4 - 6 x^2 y^2 + y^4 + a
   // y1 = 4 x^3 y - 4 x y^3 + b
   x1 = std::pow(x0, 4) - 6 * std::pow(x0, 2) * std::pow(y0, 2) + std::pow(y0, 4) + mB;
   y1 = 4 * (std::pow(x0, 3)) * y0 - 4 * x0 * (std::pow(y0, 3)) + mA;
}