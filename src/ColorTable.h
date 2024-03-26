#ifndef _COLORTABLE_H_
#define _COLORTABLE_H_

#include "PPM.h"
#include <vector>
#include <cmath>
#include <map>
#include <iostream>


void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value);
void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue);


class Color {


public:

    Color( ); // default constructor
    Color( const int& red, const int& green, const int& blue );
    int getRed( ) const;
    int getGreen( ) const;
    int getBlue( ) const;
    int getChannel( const int& channel ) const;
    void setRed( const int& value );
    void setGreen( const int& value );
    void setBlue( const int& value );
    void setChannel( const int& channel, const int& value );
    void invert( const int& max_color_value );
    bool operator==( const Color& rhs ) const;
  
    //final
    void setFromHSV(const double& hue, const double& saturation, const double& value);
    void getHSV(double& hue, double& saturation, double& value) const;
    



protected:

    int mRed;   // red channel data member
    int mGreen; // green channel data member
    int mBlue;  // blue channel data member


};

class ColorTable {

public:

    ColorTable( const int& num_color );
    int getNumberOfColors( ) const;
    void setNumberOfColors( const int& num_color );
    const Color& operator[]( const int& i ) const;
    Color& operator[]( const int& i );
    void setRandomColor( const int& max_color_value, const int& position );
    double gradientSlope(const double y1, const double y2, const double x1, const double x2) const;

    double gradientValue(const double y1, const double x1, const double slope, const double x) const;
    void insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 );
    int getMaxChannelValue( ) const; 

    // practice exam
    void insertInvertedGradient(const Color& color1, const int& position1, const int& position2);

    // exam 3
    void insertEasyRandomGradient(const int& position1, const int& position2);

    //final
    void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue);
    void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value);
    void insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2);

protected:

    std::vector<Color> mColors;


};

std::ostream& operator<<( std::ostream& os, const Color& color );

#endif /* _COLORTABLE_H_ */