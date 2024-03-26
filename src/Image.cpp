#include "Image.h"
#include <iostream>
#include <vector>

Image::Image()
    
    : mHeight(0), mWidth(0) { // initialize data members to 0.
    mData.resize(mHeight * mWidth * 3);

    }

Image::Image( const int& height, const int& width )
    : mHeight(height), mWidth(width) {
    mData.resize(mHeight * mWidth * 3);
    }

int Image::getHeight( ) const {
    return mHeight;
}

int Image::getWidth( ) const {
    return mWidth;
}

bool Image::indexValid( const int& row, const int& column, const int& channel ) const {
    // check if valid positions
     if( row >= 0 && row < mHeight && column >= 0 && column < mWidth && channel >= 0 && channel < 3 ) {
        return true;
     } else {
        return false;
     }
}

int Image::index( const int& row, const int& column, const int& channel ) const {
    int index = (row * mWidth * 3 + column * 3) + channel;
    return index;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const {
    
    bool result = indexValid(row, column, channel ) ;
    if (result == false) {
        return -1;
    } else {
        double value = mData[index(row, column, channel)];
        return value;
    }

}

void Image::setHeight( const int& height ) {
    // only non-negative values accepted
    if (height >= 0) {
        mHeight = height;
        mData.resize(mHeight * mWidth * 3);
    }
}

void Image::setWidth( const int& width ) {

    if (width >= 0) {
        mWidth = width;
        mData.resize(mHeight * mWidth * 3);
    }
}

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    
    bool check = indexValid(row, column, channel );
    if (check == true) {
        mData[ index(row, column, channel ) ] = value;
    }

}
