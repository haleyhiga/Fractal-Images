// testing
/* #include "NumberGrid.h"
#include "ComplexFractal.h"
#include "ActionData.h"
#include "image_menu.h"
#include <cmath>


void NumberGrid::calculateAllNumbers() {
  
    int row, column;
    for (row = 0; row < mHeight; row++) {
        for (column = 0; column < mWidth; column++) {
            int number = calculateNumber(row, column);
            setNumber(row, column, number);
        }
    }
}

ComplexFractal::ComplexFractal( ) 
    : NumberGrid(301, 201), mMin_x(-1.5), mMax_x(1.5), mMin_y(-1), mMax_y(1) ,deltaX(0.01), deltaY(0.01) {

    }

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
    : NumberGrid(height, width), mMin_x(min_x), mMax_x(max_x), mMin_y(min_y), mMax_y(max_y) {
            // set deltas here
    }

ComplexFractal::~ComplexFractal( ) {}

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
        double deltaX = calculateDeltaX();
        double deltaY = calculateDeltaY();
        setDeltas(deltaX, deltaY);

    }
} 

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    if ((min_x >= -2.0 && min_x <= 2.0) && (max_x >= -2.0 && max_x <= 2.0) && (min_y >= -2.0 && min_y <= 2.0) && (max_y >= -2.0 && max_y <= 2.0)) {
        if ((min_x != max_x) && (min_y != max_y)) {
             mMin_x = min_x;
             mMax_x = max_x;
             mMin_y = min_y;
             mMax_y = max_y;
             if  (min_x > max_x && min_y > max_y) {
                mMin_x = max_x;
                mMax_x = min_x;
                mMin_y = max_y;
                mMax_y = min_y;

            }
        }
        deltaX = calculateDeltaX();
        deltaY = calculateDeltaY();
        setDeltas(deltaX, deltaY);
    }
}

double ComplexFractal::getDeltaX( ) const {
    return deltaX;
}

double ComplexFractal::getDeltaY( ) const {
    return deltaY;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
    if (delta_x >= 0 && delta_y >= 0) {
        deltaX = delta_x;
        deltaY = delta_y;
    }
}

double ComplexFractal::calculateDeltaY( ) const {

    double delta_y = (mMax_y - mMin_y) / (mHeight - 1);
    return delta_y;
}

double ComplexFractal::calculateDeltaX( ) const {
 
    double delta_x = (mMax_x - mMin_x / mWidth - 1);
    return delta_x;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {
    if (column < 0 || column >= mWidth) {
        return 0;
    } else {
        double x = mMin_x + (column * getDeltaX());
    }
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if (row < 0 || row >= mHeight) {
        return 0;
    } else {
        double y = mMax_y - (row * getDeltaY());
    }
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
    if (column < 0 || row < 0) {
        x = 0;
        y = 0;
    } else {
        x = calculatePlaneXFromPixelColumn(column);
        y = calculatePlaneYFromPixelRow(row);
    }
}

int ComplexFractal::calculateNumber( const int& row, const int& column ) const {
    if (row >= 0 && row < mHeight && column >= 0 && column <= mWidth) {
        double x, y;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        int num = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
        return num;
    } else {
        return -1;
    }
}

void setFractalPlaneSize(ActionData& action_data) {
    NumberGrid *numGrid = &action_data.getGrid(); // refer to example as to why this is a reference
    ComplexFractal *complexFrac = dynamic_cast<ComplexFractal *>(numGrid);
    
    if (complexFrac != 0) { // if not 0 that means that this is a complex fractal object
       double minX = getDouble(action_data, "Min X? ");
       double maxX = getDouble(action_data, "Max X? ");
       double minY = getDouble(action_data, "Min Y? ");
       double maxY = getDouble(action_data, "Max Y? ");
       complexFrac->setPlaneSize(minX, maxX, minY, maxY);
       return;

    } else {
       action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
       return;
    }
}

void ComplexFractal::zoomPlane(const double& zoom_factor) {
    // x values
    double currentX = mMin_x - mMax_x;
    double desiredX = currentX * zoom_factor;
    double changeX = (desiredX - currentX) / 2;
    double newMinX = changeX + mMin_x;
    double newMaxX = changeX - mMax_x;
    if (newMinX < -2.0) {
        newMinX = -2.0;
    }
    if (newMaxX > 2.0) {
        newMaxX = 2.0;
    }

    // y values
    double currentY = mMin_y - mMax_y;
    double desiredY = currentY * zoom_factor;
    double changeY = (desiredY - currentY) / 2;
    double newMinY = changeY + mMin_y;
    double newMaxY = changeY - mMax_y;
    if (newMinY < -2.0) {
        newMinY = -2.0;
    }
    if (newMaxY > 2.0) {
        newMaxY = 2.0;
    }

    setPlaneSize(newMinX, newMaxX, newMinY, newMaxY);

}
 */
