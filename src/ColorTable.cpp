#include "ColorTable.h"
#include <cmath>
#include <cstdlib>
#include <iostream>


Color::Color( )
    : mRed( 0 ), mGreen( 0 ), mBlue( 0 ) {
    }

Color::Color( const int& red, const int& green, const int& blue )
    : mRed( red ), mGreen( green ), mBlue( blue ) {

    }

int Color::getRed( ) const {
    return mRed;
}

int Color::getGreen( ) const {
    return mGreen;
}

int Color::getBlue( ) const {
    return mBlue;
}

int Color::getChannel( const int& channel ) const {
    
    if (channel == 0) {
        return getRed();
    } else if (channel == 1) {
        return getGreen();
    } else if (channel == 2) {
        return getBlue();
    } else {
        return -1;
    }  

}

void Color::setRed( const int& value ) {
    if (value >= 0) { 
        mRed = value;
    }
}

void Color::setGreen( const int& value ) {
    if (value >= 0) {
        mGreen = value;
    }
}

void Color::setBlue( const int& value ) {
    if (value >= 0) {
        mBlue = value;
    }
}


void Color::setChannel( const int& channel, const int& value ) {
   
    if (value >= 0 && channel >= 0 && channel <= 2) {
        if (channel == 0) {
            mRed = value;
        } else if (channel == 1) {
            mGreen = value;
        } else if (channel == 2) {
            mBlue = value;
        }
    }
}

void Color::invert( const int& max_color_value ) {
   
    int red = getChannel(0);
    int green = getChannel(1);
    int blue = getChannel(2);
    if (max_color_value >= red && max_color_value >= green && max_color_value >= blue) {
        
        int invertedRed = max_color_value - red;
        setChannel(0, invertedRed);
       
        int invertedGreen = max_color_value - green;
        setChannel(1, invertedGreen);
        
        int invertedBlue = max_color_value - blue;
        setChannel(2, invertedBlue);
        
    }
}


bool Color::operator==( const Color& rhs ) const {
    int red_value = getRed();
    int green_value = getGreen();
    int blue_value = getBlue();

    if (rhs.getRed() == red_value && rhs.getGreen() == green_value && rhs.getBlue() == blue_value) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<( std::ostream& os, const Color& color ) {
    return os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
}


// ColorTable Class

ColorTable::ColorTable( const int& num_color ) {
    mColors.resize(num_color);
}

int ColorTable::getNumberOfColors( ) const {
    return mColors.size();
}

void ColorTable::setNumberOfColors( const int& num_color ) {
    mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const {
   
    int size = mColors.size();
   
    if (i >= 0 && i < size) {
        return mColors[i];
    } else { // returns static color object, prevents lvalue error
        static Color ec( -1, -1, -1 );
        static Color c( -1, -1, -1 );
        c = ec;
        return c;

    }
}

Color& ColorTable::operator[]( const int& i ) {
    
    int size = mColors.size();
   
    if (i >= 0 && i < size) {
        return mColors[i];
    } else { // returns static color object
        static Color ec( -1, -1, -1 );
        static Color c( -1, -1, -1 );
        c = ec;
        return c;

    }
}


void ColorTable::setRandomColor( const int& max_color_value, const int& position ) {
    // check if position is valid and max color value is >= 0
    int size = mColors.size();

    if (position < size && position >= 0 && max_color_value >= 0) {
        
        int rRed = (std::rand() % (max_color_value + 1)); // The random values are between 0 and max_color_value, inclusive
        int rGreen = (std::rand() % (max_color_value + 1));
        int rBlue = (std::rand() % (max_color_value + 1));

        mColors[position].setRed(rRed); // Assigns the positionth color random values for all three channels.
        mColors[position].setGreen(rGreen);
        mColors[position].setBlue(rBlue);
        
    }
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {

    double slope = (y2 - y1) / (x2 - x1);
    return slope; 
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
    double valueY = (slope * (x - x1)) + y1;
    return valueY;
}


void ColorTable::insertGradient( const Color& color1, const Color& color2, const int& position1, const int& position2 ) {

    if (position1 < position2 && position1 >= 0 && position2 >= 0 && position1 < getNumberOfColors() && position2 < getNumberOfColors()) {

       double redSlope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
       double greenSlope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
       double blueSlope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);

      int position; // will represent the position its in
       for (position = position1; position <= position2; position++) {
        // assign new color change into the colortable colors.
        mColors[position].setRed(gradientValue(color1.getRed(), position1, redSlope, position));
        mColors[position].setGreen(gradientValue(color1.getGreen(), position1, greenSlope, position));
        mColors[position].setBlue(gradientValue(color1.getBlue(), position1, blueSlope, position));

    }
    }

}





void ColorTable::insertInvertedGradient(const Color& color1, const int& position1, const int& position2) {
    
    Color copyColor1 = color1;
    copyColor1.invert(255);
    insertGradient(color1, copyColor1, position1, position2);

}


int ColorTable::getMaxChannelValue( ) const {

    int biggest = 0; 
    int r, g, b;
    int size = mColors.size(); // idk why i always used size when i could use getNumberOfColors?!

    
    for (int i = 0; i < size; i++) {
        r = mColors[i].getRed();
        g = mColors[i].getGreen();
        b = mColors[i].getBlue();

        if (r > biggest) {
            biggest = r;
        } if (g > biggest) {
            biggest = g;
        } if (b > biggest) {
            biggest = b;
        }
        
    }
    return biggest;
} 

void ColorTable::insertEasyRandomGradient(const int& position1, const int& position2) {

    ColorTable color1(getNumberOfColors());
    ColorTable color2(getNumberOfColors());
    color1.setRandomColor(255, position1);
    color2.setRandomColor(255, position2);



    if (position1 < position2 && position1 >= 0 && position2 >= 0 && position1 < getNumberOfColors() && position2 < getNumberOfColors()) {

      // double redSlope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
      // double greenSlope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
      // double blueSlope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);

      int position; // will represent the position its in
       for (position = position1; position <= position2; position++) {
        // assign new color change into the colortable colors. 
        // ill come back to this
/*         mColors[position].setRed(insertGradient(color1, color2, position, position2));
        mColors[position].setGreen(gradientValue(color1.getGreen(), position1, greenSlope, position));
        mColors[position].setBlue(gradientValue(color1.getBlue(), position1, blueSlope, position));
 */
    }
    }
}


// HSV

//////////////////////////////////////////////////////////////////////////
///
void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue) {
  /* Convert Hue, Saturation, Value to Red, Green, Blue
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
   *
   * Inputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   *
   * Outputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   */
  if(hue < 0.0 || hue > 360.0 || saturation < 0.0 || saturation > 1.0 || value < 0.0 || value > 1.0) {
    red = green = blue = 0.0;
    std::cerr << "HSV_to_RGB() input parameters out of range." << std::endl
              << " hue: " << hue  << std::endl
              << " saturation: " << saturation << std::endl
              << " value: " << value << std::endl;
    return;
  }

  // chroma selects the strength of the "primary" color of the current area of the wheel
  double chroma = value * saturation;
  // hue2 selects which 60-degree wedge of the color wheel we are in
  double hue2 = hue / 60.0;
  // x selects the strength of the "secondary" color of the current area of the wheel
  double x = chroma * ( 1 - std::abs( std::fmod( hue2, 2 ) - 1 ) );
  if( hue2 >= 0 && hue2 < 1 ) {
    red = chroma;
    green = x;
    blue = 0.0;
  } else if( hue2 >= 1 && hue2 < 2 ) {
    red = x;
    green = chroma;
    blue = 0.0;
  } else if( hue2 >= 2 && hue2 < 3 ) {
    red = 0.0;
    green = chroma;
    blue = x;
  } else if( hue2 >= 3 && hue2 < 4 ) {
    red = 0.0;
    green = x;
    blue = chroma;
  } else if( hue2 >= 4 && hue2 < 5 ) {
    red = x;
    green = 0.0;
    blue = chroma;
  } else if( hue2 >= 5 && hue2 <= 6 ) {
    red = chroma;
    green = 0.0;
    blue = x;
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  // m scales all color channels to obtain the overall brightness.
  double m = value - chroma;
  red = 255.0*( red + m );
  green = 255.0*( green + m );
  blue = 255.0*( blue + m );
}

void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value) {
  /* Red, Green, Blue to Convert Hue, Saturation, Value
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
   *
   * Inputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   *
   * Outputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   */
  if(red0 < 0.0 || red0 > 255.0 || green0 < 0.0 || green0 > 255.0 || blue0 < 0.0 || blue0 > 255.0) {
    hue = saturation = value = 0.0;
    std::cerr << "RGB_to_HSV() input parameters out of range." << std::endl
              << " red: " << red0  << std::endl
              << " green: " << green0 << std::endl
              << " blue: " << blue0 << std::endl;
    return;
  }

  double red   = red0 / 255.0;
  double green = green0 / 255.0;
  double blue  = blue0 / 255.0;

  // x_max helps identify the primary hue
  double x_max = red;
  if(green > x_max) { x_max = green; }
  if(blue > x_max) { x_max = blue; }
  value = x_max;

  double x_min = red;
  if(green < x_min) { x_min = green; }
  if(blue < x_min) { x_min = blue; }

  double chroma = x_max - x_min;

  if(chroma == 0) {
    hue = 0;
  } else if(value == red) {
    hue = 60.0 * (0 + (green - blue)/chroma);
  } else if(value == green) {
    hue = 60.0 * (2 + (blue - red)/chroma);
  } else if(value == blue) {
    hue = 60.0 * (4 + (red - green)/chroma);
  } else {
    hue = -720.0;
  }
  if(hue < 0.0) {
    hue += 360.0;
  }

  if(value == 0.0) {
    saturation = 0.0;
  } else {
    saturation = chroma/value;
  }

}
///
//////////////////////////////////////////////////////////////////////////

void Color::setFromHSV(const double& hue, const double& saturation, const double& value) {
    double r = getRed();
    double g = getGreen();
    double b = getBlue();

    HSV_to_RGB(hue, saturation, value, r, g, b);
    setRed(r);
    setGreen(g);
    setBlue(b);


}

void Color::getHSV(double& hue, double& saturation, double& value) const {
    RGB_to_HSV(mRed, mGreen, mBlue, hue, saturation, value);
}

/*
make sure the positions are valid
get the HSV values from both colors
calculate the hue slope, the saturation slope, and the value slope (using gradientSlope())
for each position in the gradient
    calculate the hue, the saturation, and the value. (using gradientValue())
    set a color using the HSV (previous exam task has these conversions)
    assign the color into the correct position in the color table.
    */

void ColorTable::insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2) {

    
    if (position1 < position2 && position1 >= 0 && position2 >= 0 && position1 < getNumberOfColors() && position2 < getNumberOfColors()) {
         double hueColor1, satColor1, valueColor1;
         double hueColor2, satColor2, valueColor2;
        
        // get HSV values from both colors
        color1.getHSV(hueColor1, satColor1, valueColor1);
        color2.getHSV(hueColor2, satColor2, valueColor2);

        // calculate the hue slope, sat slope, and value slope using gradientSlope()
        double hueSlope = gradientSlope(hueColor1, hueColor2, position1, position2);
        double satSlope = gradientSlope(satColor1, satColor2, position1, position2);
        double valueSlope = gradientSlope(valueColor1, valueColor2, position1, position2);
        
        int position;
        for (position = position1; position <= position2; position++) {
            // calc the hsv using gradientValue()
            double hue = gradientValue(hueColor1, position1, hueSlope, position);
            double sat = gradientValue(satColor1, position1, satSlope, position);
            double value = gradientValue(valueColor1, position1, valueSlope, position);

            // set a color using the hsv
            Color c;
            c.setFromHSV(hue, sat, value);
            // assign the color to the correct position in the colortable
            mColors[position].setRed(c.getRed());
            mColors[position].setGreen(c.getGreen());
            mColors[position].setBlue(c.getBlue());

        }

         
    }
}

