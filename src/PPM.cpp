#include "PPM.h"
#include "Image.h"
#include <iostream>
#include <vector>
#include <fstream>


PPM::PPM( )
  : mMaxColor( 1 ) {
}

PPM::PPM( const int& height, const int& width ) 
  : Image(height, width), mMaxColor(1) {
}

int PPM::getMaxColorValue( ) const {
    return mMaxColor;
}

bool PPM::valueValid( const int& value ) const {
    if (value >= 0 && value <= mMaxColor) {
        return true;
    } else {
        return false;
    }
}

void PPM::setMaxColorValue( const int& max_color_value ) {
    if (max_color_value >= 1 && max_color_value <= 255) {
        mMaxColor = max_color_value;
    }
}

void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    int check = valueValid(value);
    if (check == true) {
        Image::setChannel(row, column, channel, value );
    }
}

void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue ) {
    setChannel(row, column, 0, red);
    setChannel(row, column, 1, green);
    setChannel(row, column, 2, blue);
}


void PPM::writeStream(std::ostream& os) const {
    
    int height = getHeight();
    int width = getWidth();
    int maxcolor = getMaxColorValue();
    int row, column, channel;

    os << "P6" << " " << width << " " << height << " " << maxcolor << std::endl;

    for( row = 0; row < height; row ++ ) {
        for( column = 0; column < width; column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                unsigned char c = getChannel(row, column, channel);
                os.write((char *) &c, sizeof(c));

    }
     }
    }


}


void PPM::readStream(std::istream& is) {
    
    std::string type;
    int imagewidth;
    int imageheight;
    int max_color;
    unsigned char c;

    unsigned char r;
    unsigned char g;
    unsigned char b;

    is >> type >> imagewidth >> imageheight >> max_color;
    
    //reads one byte for newline char
    is.read((char *) &c, sizeof(c));
    
    Image::setHeight(imageheight);
    Image::setWidth(imagewidth);
    setMaxColorValue(max_color);

    for( int row = 0; row < imageheight; row ++ ) {
        for( int column = 0; column < imagewidth; column ++ ) {
                is.read((char *) &r, sizeof(c));
                is.read((char *) &g, sizeof(c));
                is.read((char *) &b, sizeof(c));
                setPixel(row, column, r, g, b);

            }
        }
    }


// ppm operators

bool PPM::operator==( const PPM& rhs ) const {
    
    int pixels = getWidth() * getHeight();

    if ((rhs.getWidth() * rhs.getHeight()) == pixels) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator!=( const PPM& rhs ) const {
    
    int pixels = getWidth() * getHeight();

    if ((rhs.getWidth() * rhs.getHeight()) != pixels)  {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator<( const PPM& rhs ) const {
    
    int pixels = getWidth() * getHeight();

    if ((pixels) < (rhs.getWidth() * rhs.getHeight()))  {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator<=( const PPM& rhs ) const {
    
    int pixels = getWidth() * getHeight();

    if ((pixels) <= (rhs.getWidth() * rhs.getHeight())) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator>( const PPM& rhs ) const {
    
    int pixels = getWidth() * getHeight();

    if ((pixels) > (rhs.getWidth() * rhs.getHeight())) {
        return true;
    } else {
        return false;
    }
}

bool PPM::operator>=( const PPM& rhs ) const {
    
    int pixels = getWidth() * getHeight();

    if ((pixels) >= (rhs.getWidth() * rhs.getHeight())) {
        return true;
    } else {
        return false;
    }
}

PPM& PPM::operator+=( const PPM& rhs ) {
    

    /*Assumes *this and rhs have the same width and height. Adds the channel values from rhs into the channels for *this. 
    If the resulting value is larger than max color value, set to max color value. Returns *this.*/
    int row, column, channel;
    int height = getHeight();
    int width = getWidth();
    int maxcolor = getMaxColorValue();
    
    for (row=0; row < height; row ++) {
        for (column=0; column < width; column++) {
            for (channel=0; channel < 3; channel++) {
                 int result = (getChannel(row, column, channel) + rhs.getChannel(row, column, channel));
                    if (result > maxcolor) {
                        result = maxcolor;
                }
               setChannel(row, column, channel, result);
                }
            }
            }
            return *this;
        }
    


PPM& PPM::operator-=( const PPM& rhs ) {
    
    /* Assumes *this and rhs have the same width and height. 
    Subtracts the channel values from rhs from the channels for *this. If the resulting value is less than 0, set to 0. Returns *this.*/

    int row, column, channel;
    int height = getHeight();
    int width = getWidth();
    
    for (row=0; row < height; row ++) {
        for (column=0; column < width; column++) {
            for (channel=0; channel < 3; channel++) {
                 int result = (getChannel(row, column, channel) - rhs.getChannel(row, column, channel));
                if (result < 0) {
                    result = 0;
                }
               setChannel(row, column, channel, result);
                }
            }
            }
            return *this;
        }
    

PPM& PPM::operator*=( const double& rhs ) {
    
    /*  Multiples every channel value of *this by rhs. If the resulting value is larger than max color value, set to max color value.
     If the resulting value is less than 0, set to 0. Returns *this.*/


    int row, column, channel;
    int height = getHeight();
    int width = getWidth();

    
    for( row = 0; row < height; row ++ ) {
        for( column = 0; column < width; column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                int result = getChannel(row, column, channel) * (rhs);

                if (result > getMaxColorValue()) {
                    result = getMaxColorValue();
                 }
                else if (result < 0) {
                  result = 0;
                }
                setChannel(row, column, channel, result);
                }
}
    }
    return *this;
}



PPM& PPM::operator/=( const double& rhs ) {
    
    /* Divides every channel value of *this by rhs. If the resulting value is larger than max color value, set to max color value.
     If the resulting value is less than 0, set to 0. Returns *this.*/

    int row, column, channel;
    int height = getHeight();
    int width = getWidth();

    for( row = 0; row < height; row ++ ) {
        for( column = 0; column < width; column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                int result = ( getChannel(row, column, channel) / rhs);
                 if (result < 0) {
                     result = 0;
            }
                else if (result > getMaxColorValue()) {
                    result = getMaxColorValue();
            }
            setChannel(row, column, channel, result);
}
    }
    
}
    return *this;
} 



PPM PPM::operator+( const PPM& rhs ) const {
    

    PPM obj(this->getHeight(), this->getWidth());

    obj.setMaxColorValue(this->getMaxColorValue());
    

    int row, column, channel;

    for( row = 0; row < obj.getHeight(); row ++ ) {
        for( column = 0; column < obj.getWidth(); column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                int result = (this->getChannel(row, column, channel) + rhs.getChannel(row, column, channel));
                if (result > obj.getMaxColorValue()) {
                    obj.setChannel(row, column, channel, obj.getMaxColorValue());
                } else {
                    obj.setChannel(row, column, channel, result);
                }
                }
            }
        }
        return obj;
    }



PPM PPM::operator-( const PPM& rhs ) const {

    PPM obj(this->getHeight(), this->getWidth());

    obj.setMaxColorValue(this->getMaxColorValue());
    

    int row, column, channel;

    for( row = 0; row < obj.getHeight(); row ++ ) {
        for( column = 0; column < obj.getWidth(); column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                int result = (this->getChannel(row, column, channel) - rhs.getChannel(row, column, channel));
                if (result < 0) {
                    obj.setMaxColorValue(0);
                }
            obj.setChannel(row, column, channel, result);
                
            }
        }
    }
    return obj;
    }

PPM PPM::operator*( const double& rhs ) const {

    PPM obj(this->getHeight(), this->getWidth());

    obj.setMaxColorValue(this->getMaxColorValue());
    

    int row, column, channel;

    for( row = 0; row < obj.getHeight(); row ++ ) {
        for( column = 0; column < obj.getWidth(); column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                // multiply by the value of rhs
                int result = (this->getChannel(row, column, channel) * rhs);
                if (result > obj.getMaxColorValue()) {

                    result = obj.getMaxColorValue();
                } else if (result < 0) {
                    result = 0;
                }
                obj.setChannel(row, column, channel, result);
                
            }
        }
    }
    return obj;
    }






PPM PPM::operator/( const double& rhs ) const {
    
  PPM obj(this->getHeight(), this->getWidth());

    obj.setMaxColorValue(this->getMaxColorValue());
    

    int row, column, channel;

    for( row = 0; row < obj.getHeight(); row ++ ) {
        for( column = 0; column < obj.getWidth(); column ++ ) {
            for(channel = 0; channel < 3; channel ++) {
                // multiply by the value of rhs
                int result = (this->getChannel(row, column, channel) / rhs);
                if (result > obj.getMaxColorValue()) {
                    result = obj.getMaxColorValue();
                } else if (result < 0) {
                    result = 0;
                }
                obj.setChannel(row, column, channel, result);
                
            }
        }
    }
    return obj;
    }

 // image filters
void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const {

    dst.setHeight(this->getHeight());
    dst.setWidth(this->getWidth());
    dst.setMaxColorValue(this->getMaxColorValue());

    int row, column;
    int value;

    for (row = 0; row < dst.getHeight(); row++) {
        for (column = 0; column < dst.getWidth(); column++) { {
            value = getChannel(row, column, src_channel);
            dst.setPixel(row, column, value, value, value);
    
    }
}
 }
}

 void PPM::grayFromRed( PPM& dst ) const {
    grayFromChannel(dst, 0);
 }

 void PPM::grayFromGreen( PPM& dst ) const {
    grayFromChannel(dst, 1);
 }

 void PPM::grayFromBlue( PPM& dst ) const {
    grayFromChannel(dst, 2);
 }

 double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const {
    
    int redpixel = getChannel(row, column, 0);
    int greenpixel = getChannel(row, column, 1);
    int bluepixel = getChannel(row, column, 2);
    return ((0.2126 * redpixel) + (0.7152 * greenpixel) + (0.0722 * bluepixel));

 }

 void PPM::grayFromLinearColorimetric( PPM& dst ) const {
    
    int row, column;

    dst.setHeight(this->getHeight());
    dst.setWidth(this->getWidth());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (row = 0; row < dst.getHeight(); row++) {
        for (column = 0; column < dst.getWidth(); column++) {
            int value = linearColorimetricPixelValue(row, column);
            dst.setChannel(row, column, 0, value);
            dst.setChannel(row, column, 1, value);
            dst.setChannel(row, column, 2, value);
        }
    }

 }

