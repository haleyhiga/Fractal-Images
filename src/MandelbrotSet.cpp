#include "MandelbrotSet.h"

#include <cmath>
#include <iostream>

MandelbrotSet::MandelbrotSet( ) 
    : ComplexFractal() {

    }

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : ComplexFractal(height, width, min_x, max_x, min_y, max_y) {
    }

MandelbrotSet::~MandelbrotSet( ) {} // destructor

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
    //x' = x*x - y*y + a
    //y' = 2*x*y + b

    x1 = ((x0 * x0) - (y0 * y0)) + a;
    y1 = (2 * x0 * y0) + b;

}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {

    // taking a for loop to this approach instead of while loop :)
    int escapeCount;
    double x1, y1;
    double x = 0;
    double y = 0;

    calculateNextPoint(x, y, a, b, x1, y1);
    x = x1;
    y = y1;

    for (escapeCount = 0; escapeCount < mMaxNumber; escapeCount++) {
        calculateNextPoint(x, y, a, b, x1, y1);
        if (x * x + y * y > 4.0) { // check if escaped
            return escapeCount;
        }
        x = x1;
        y = y1;
    }
    return escapeCount;
}


int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
       
    double x, y;

    if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        return calculatePlaneEscapeCount(x, y);
    } else {
        return -1;
    }
} 
