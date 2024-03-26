#include "ComplexFractal.h"
#include "NumberGrid.h"
#include <iostream>
#include <cmath>

ComplexFractal::ComplexFractal( )
    : ThreadedGrid(201, 301), mMin_x( -1.5 ), mMax_x( 1.5 ), mMin_y( -1 ), mMax_y( 1 ), deltaX( 0.01 ), deltaY( 0.01 ) {
        // 301 x 201 grid
    }

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y ) 
    : ThreadedGrid(height, width), mMin_x( min_x ), mMax_x( max_x ), mMin_y( min_y ), mMax_y( max_y ), deltaX( 0 ), deltaY( 0 ) {
        setDeltas(calculateDeltaX(), calculateDeltaY());
        //mNumbers.resize(mHeight * mWidth);
}

ComplexFractal::~ComplexFractal( ) {} // destructor

double ComplexFractal::getMinX( ) const {
    return mMin_x;
}

double ComplexFractal::getMaxX( ) const {
    return mMax_x;
}

double ComplexFractal::getMinY( ) const {
    return mMin_y;
}

double ComplexFractal::getMaxY( ) const {
    return mMax_y;
}

void ComplexFractal::setGridSize( const int& height, const int& width ) {
    
    if (height >= 2 && width >= 2) {

        NumberGrid::setGridSize(height, width);
        deltaX = calculateDeltaX();
        deltaY = calculateDeltaY();
        setDeltas(deltaX, deltaY);
    }

}

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    
    if ((min_x >= -2 && min_x <= 2) && (min_y >= -2 && min_y <= 2) && (max_x >= -2 && max_x <= 2) && (max_y >= -2 && max_y <= 2)) {
        if ((min_x != max_x) && (min_y != max_y)) {
            if (min_x > max_x) {
                mMax_x = min_x; 
                mMin_x = max_x;
            } else {
                mMax_x = max_x;
                mMin_x = min_x;
            }
            if (min_y > max_y) {
                mMax_y = min_y; 
                mMin_y = max_y;  // i hope this works
            } else {
                mMax_y = max_y;
                mMin_y = min_y;
            }
            double deltaX = calculateDeltaX(); 
            double deltaY = calculateDeltaY();
            setDeltas(deltaX, deltaY);

        }
    }
}

double ComplexFractal::getDeltaX( ) const {
    return deltaX;
}

double ComplexFractal::getDeltaY( ) const {
    return deltaY;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
   
    if (delta_x > 0 && delta_y > 0) { 
        deltaX = delta_x;
        deltaY = delta_y;
    }
}

double ComplexFractal::calculateDeltaY( ) const {
    double delta_y = (mMax_y - mMin_y) / (mHeight - 1);
    return delta_y;
}

double ComplexFractal::calculateDeltaX( ) const {
    double delta_x = (mMax_x - mMin_x) / (mWidth - 1);
    return delta_x;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {

    if (column < 0 || column >= mWidth) {
        return 0;
    } else {
        double xValue = mMin_x + (column * (getDeltaX()));
        return xValue;
    }
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if (row < 0 || row >= mHeight) {
        return 0;
    } else {
        double yValue = mMax_y - (row * (getDeltaY()));
        return yValue;
    }
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
     // Sets x and y to the plane coordinates for the row and column. 
     // If either row or column is out of range, set both x and y to 0. Notice x and y are return by reference.
    
    if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
        x = calculatePlaneXFromPixelColumn(column);
        y = calculatePlaneYFromPixelRow(row);
    } else {
        x = 0;
        y = 0;
    }

}

int ComplexFractal::calculateNumber( const int& row, const int& column ) const {
    if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
      double x, y;
      calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
      int value = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
      return value;
    } else {
        return -1;
    }
}
