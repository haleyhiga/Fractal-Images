#include "NumberGrid.h"
#include "PPM.h"
#include "ColorTable.h"
#include <iostream>


NumberGrid::NumberGrid( )
    : mMaxNumber( 255 ), mHeight( 300 ), mWidth( 400 ) { 
        mNumbers.resize(mHeight * mWidth);
        for (int i = 0; i < (mHeight * mWidth); i++) {
            mNumbers[i] = 0;
        }

    }

NumberGrid::NumberGrid( const int& height, const int& width ) 
    : mMaxNumber( 255 ), mHeight( height ), mWidth( width ) {
        mNumbers.resize(mHeight * mWidth);
        for (int i = 0; i < (mHeight * mWidth); i++) {
            mNumbers[i] = 0;
        }

    }

// destructor
NumberGrid::~NumberGrid() {

}

int NumberGrid::getHeight( ) const {
    
    return mHeight;
}

int NumberGrid::getWidth( ) const {
    
    return mWidth;
}

int NumberGrid::getMaxNumber( ) const {
    
    return mMaxNumber;
}

void NumberGrid::setGridSize( const int& height, const int& width ) {

    if ((height >= 2) && (width >= 2)) {
      mHeight = height;
      mWidth = width;
      mNumbers.resize(mHeight * mWidth);
    }
}

void NumberGrid::setMaxNumber( const int& number ) {

    if (number >= 0) {
        mMaxNumber = number;
    }
}

const std::vector< int >& NumberGrid::getNumbers( ) const {
    
    return mNumbers;
}

int NumberGrid::index( const int& row, const int& column ) const {
    
    int index = row * mWidth + column;
    return index;
}

bool NumberGrid::indexValid( const int& row, const int& column ) const {
    
    if( row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
        return true;
     } else {
        return false;
     }
}

bool NumberGrid::numberValid( const int& number ) const {
    if (number >= 0 && number <= mMaxNumber) {
        return true;
    } else {
        return false;
    }
}

int NumberGrid::getNumber( const int& row, const int& column ) const {
    
    bool result = indexValid(row, column) ;
    if (result == false) {
        return -1;
    } else {
        int position = index(row, column);
        return mNumbers[position];
    }
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number ) {
    
    bool checkIndex = indexValid(row, column);
    bool validNum = numberValid(number);
    if (checkIndex == true && validNum == true) {
        mNumbers[ index(row, column) ] = number;
    }
}

void NumberGrid::setPPM( PPM& ppm ) const {
     
    /* i used to have ppm.setHeight(this->mHeight);
    ppm.setWidth(this->mWidth) which does the same thing because this-> is a pointer to the object */
    ppm.setHeight(mHeight);
    ppm.setWidth(mWidth);
    ppm.setMaxColorValue(63);

    int row, column;

    for (row = 0; row < mHeight; row++) {
        for (column = 0; column < mWidth; column++) {
            int number = getNumber(row, column);
            if (number == 0) {
                ppm.setPixel(row, column, 0, 0, 0);
            }
            else if (number == mMaxNumber) {
                ppm.setPixel(row, column, 63, 31, 31);
            }
            else if (number % 8 == 0) {
                ppm.setPixel(row, column, 63, 63, 63);
            }
            else if (number % 8 == 1) {
                ppm.setPixel(row, column, 63, 31, 31);
            }
            else if (number % 8 == 2) {
                ppm.setPixel(row, column, 63, 63, 31);
            }
            else if (number % 8 == 3) {
                ppm.setPixel(row, column, 31, 63, 31);
            }
            else if (number % 8 == 4) {
                ppm.setPixel(row, column, 0, 0, 0);
            }
            else if (number % 8 == 5) {
                ppm.setPixel(row, column, 31, 63, 63);
            }
            else if (number % 8 == 6) {
                ppm.setPixel(row, column, 31, 31, 63);
            }
            else if (number % 8 == 7) {
                ppm.setPixel(row, column, 63, 31, 63);
            }
        }
    }
}


void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const {
    

    // don't do anything if not at least 2 colors
    if (colors.getNumberOfColors() >= 2) {

        ppm.setHeight(mHeight); // set the width and height to match the grid
        ppm.setWidth(mWidth);
        ppm.setMaxColorValue(colors.getMaxChannelValue());

        int row, column, highestIndex, index;

        for (row = 0; row < mHeight; row++) {
            for (column = 0; column < mWidth; column++) {
                int number = getNumber(row, column);
                if (number == getMaxNumber()) {
                    highestIndex = colors.getNumberOfColors() -1;  // have to do -1 to get the highest index
                    ppm.setChannel(row, column, 0, colors[highestIndex].getRed());
                    ppm.setChannel(row, column, 1, colors[highestIndex].getGreen());
                    ppm.setChannel(row, column, 2, colors[highestIndex].getBlue());
                } else {
                    index = (getNumber(row, column) % colors.getNumberOfColors());
                    ppm.setChannel(row, column, 0, colors[index].getRed());
                    ppm.setChannel(row, column, 1, colors[index].getGreen());
                    ppm.setChannel(row, column, 2, colors[index].getBlue());
                }

            } 

        }
    }

}

void NumberGrid::calculateAllNumbers() {
    // For every (row,column) pair, calls calculateNumber to get a number and setNumber to store it.

    int row, column;
    for (row = 0; row < mHeight; row++) {
        for (column = 0; column < mWidth; column++) {
           int calcNum = calculateNumber(row, column);
           setNumber(row, column, calcNum);
           
            }
        }
}

