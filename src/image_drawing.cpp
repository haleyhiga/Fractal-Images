#include "ComplexFractal.h"
#include "image_menu.h"
#include "ActionData.h"
#include "MenuData.h"
#include "Image.h"
#include "PPM.h"
#include "JuliaSet.h"

#include <iostream>
#include <cmath>


void diagonalQuadPattern( ActionData& action_data ) {

     int height = getInteger( action_data, "Image height? " );
     int width = getInteger( action_data, "Image width? " );

     action_data.getInputImage1().setWidth(width);
     action_data.getInputImage1().setHeight(height);

     action_data.getInputImage1().setMaxColorValue(255);
    
    int row, column;

     // green
     for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
        for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          action_data.getInputImage1().setChannel(row, column, 1, ( 2*row + 2*column ) % 256);
    }
     }
    

    // red
      for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
        for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          if (row < (action_data.getInputImage1().getHeight( ) / 2)) {
            action_data.getInputImage1().setChannel(row, column, 0, 0);
          } else {
            action_data.getInputImage1().setChannel(row, column, 0, 255);
          }
        }
    }
    
     // blue
     for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
         for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          if (column < (action_data.getInputImage1().getWidth( ) / 2)) {
            action_data.getInputImage1().setChannel(row, column, 2, 0);
          } else {
            action_data.getInputImage1().setChannel(row, column, 2, 255);
          }

          
  }

     }
}

void stripedDiagonalPattern( ActionData& action_data ) {

     int height = getInteger( action_data, "Image height? " );
     int width = getInteger( action_data, "Image width? " );
     int row, column;

     action_data.getInputImage1().setHeight(height);
     action_data.getInputImage1().setWidth(width);

     int maxcolor = (height + width) / 3;

     if (maxcolor > 255) {
        action_data.getInputImage1().setMaxColorValue(255);
     } else {
        action_data.getInputImage1().setMaxColorValue(maxcolor);
     }

     // red set channels : top half = 0, bottom half = if multiples of 3
     for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
        for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          if (row < (action_data.getInputImage1().getHeight( ) / 2)) {
            action_data.getInputImage1().setChannel(row, column, 0, 0);
          } else if (row % 3 == 0) {
            action_data.getInputImage1().setChannel(row, column, 0, 0);
          } else {
            action_data.getInputImage1().setChannel(row, column, 0, action_data.getInputImage1().getMaxColorValue());
          }
        }
    }

    // green
    for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
        for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          action_data.getInputImage1().setChannel(row, column, 1, ((row + width - column - 1) % (action_data.getInputImage1().getMaxColorValue() + 1)));
    }
     }

    // blue : set to 0 if column number is less than row.  else set to maximum color value
    for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
        for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          if (column < row) {
            action_data.getInputImage1().setChannel(row, column, 2, 0);
          } else {
            action_data.getInputImage1().setChannel(row, column, 2, action_data.getInputImage1().getMaxColorValue());
          }
    }
     }

}


void setSize( ActionData& action_data ) {

   int height = getInteger(action_data, "Height? ");
   int width = getInteger(action_data, "Width? ");
   action_data.getInputImage1().setHeight(height);
   action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue( ActionData& action_data ) {

     int maxColor = getInteger(action_data, "Max color value? ");
     action_data.getInputImage1().setMaxColorValue(maxColor);
}

void setChannel( ActionData& action_data ) {

     int row = getInteger(action_data, "Row? ");
     int column = getInteger(action_data, "Column? ");
     int channel = getInteger(action_data, "Channel? ");
     int value = getInteger(action_data, "Value? ");
     action_data.getInputImage1().setChannel(row, column, channel, value);
}

void setPixel( ActionData& action_data ) {

      int row = getInteger(action_data, "Row? ");
      int column = getInteger(action_data, "Column? ");
      int red = getInteger(action_data, "Red? ");
      int green = getInteger(action_data, "Green? ");
      int blue = getInteger(action_data, "Blue? ");
      // suppose to set value
      action_data.getInputImage1().setPixel(row, column, red, green, blue);
}

void clearAll( ActionData& action_data ) {
    
    int row, column;

    for( row = 0; row < action_data.getInputImage1().getHeight( ); row ++ ) {
        for( column = 0; column < action_data.getInputImage1().getWidth( ); column ++ ) {
          action_data.getInputImage1().setPixel(row, column, 0, 0, 0);
        }
    }

}
 

// image filters
  void drawCircle(ActionData& action_data) {

   int centerrow = getInteger(action_data, "Center Row? ");
   int centercolumn = getInteger(action_data, "Center Column? ");
   int radius = getInteger(action_data, "Radius? ");
   int red = getInteger(action_data, "Red? ");
   int green = getInteger(action_data, "Green? ");
   int blue = getInteger(action_data, "Blue? ");
   int row, column;


   for (row = (centerrow - radius) - 1; row >= (centerrow - radius - 1) && row <= (centerrow + radius + 1); row++) {
      for (column = (centercolumn - radius) - 1; column >= (centercolumn - radius - 1) && (column <= (centercolumn + radius + 1)); column++) {
            double result = (std::sqrt(((column - centercolumn) * (column - centercolumn)) + ((row - centerrow) * (row - centerrow))));
            if (result <= (double) radius) {
                action_data.getInputImage1().setPixel(row, column, red, green, blue);
            }
  }
}
}

void drawBox(ActionData& action_data) {

   int toprow = getInteger(action_data, "Top Row? ");
   int leftcolumn = getInteger(action_data, "Left Column? ");
   int bottomrow = getInteger(action_data, "Bottom Row? ");
   int rightcolumn = getInteger(action_data, "Right Column? ");
   int red = getInteger(action_data, "Red? ");
   int green = getInteger(action_data, "Green? ");
   int blue = getInteger(action_data, "Blue? ");
   int row, column;

   for (row = toprow; row >= toprow && row <= bottomrow; row++) { 
        for (column = leftcolumn; column >= leftcolumn && column <= rightcolumn; column++) {
            action_data.getInputImage1().setPixel(row, column, red, green, blue);
        }
    }
} 


void drawSquare(ActionData& action_data) {

    int centerrow = getInteger(action_data, "Row? ");
    int centercolumn = getInteger(action_data, "Column? ");
    int size = getInteger(action_data, "Size? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    int radius = size / 2;
    int row, column;

   for (row = (centerrow - radius); row <= (centerrow + radius) && row >= (centerrow - radius); row++) {
        for (column = (centercolumn - radius); column <= (centercolumn + radius) && column >= (centercolumn - radius); column++) {
            action_data.getInputImage1().setPixel(row, column, red, green, blue);
        }
    }
}

// Number Grid

void configureGrid(ActionData& action_data) {
      
      int height = getInteger(action_data, "Grid Height? ");
      int width = getInteger(action_data, "Grid Width? ");
      int maxvalue = getInteger(action_data, "Grid Max Value? ");

      // configure the grid without creating a new numbergrid object 
      action_data.getGrid().setGridSize(height, width);
      action_data.getGrid().setMaxNumber(maxvalue);

}

void setGrid(ActionData& action_data) {
     
     int row = getInteger(action_data, "Grid Row? ");
     int column = getInteger(action_data, "Grid Column? ");
     int value = getInteger(action_data, "Grid Value? ");

     // sets a number in the number grid object of actiondata

     action_data.getGrid().setNumber(row, column, value);
}

void applyGrid(ActionData& action_data) {
    
    action_data.getGrid().setPPM(action_data.getOutputImage());
}



// Color Table
 void setColorTableSize(ActionData& action_data) {

    int size = getInteger(action_data, "Size? ");
    action_data.getTable().setNumberOfColors(size);

}

void setColor(ActionData& action_data) {

    int position = getInteger(action_data, "Position? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");

    action_data.getTable()[position].setRed(red); 
    action_data.getTable()[position].setGreen(green);
    action_data.getTable()[position].setBlue(blue);

}

void setRandomColor(ActionData& action_data) {

    int position = getInteger(action_data, "Position? ");
    action_data.getTable().setRandomColor(255, position);

}

void setColorGradient(ActionData& action_data) {

    int firstPosition = getInteger(action_data, "First position? ");
    int firstRed = getInteger(action_data, "First red? ");
    int firstGreen = getInteger(action_data, "First green? ");
    int firstBlue = getInteger(action_data, "First blue? ");
    int secondPosition = getInteger(action_data, "Second position? ");
    int secondRed = getInteger(action_data, "Second red? ");
    int secondGreen = getInteger(action_data, "Second green? ");
    int secondBlue = getInteger(action_data, "Second blue? ");
    
    Color firstColor(firstRed, firstGreen, firstBlue);
    Color secondColor(secondRed, secondGreen, secondBlue);
    
    action_data.getTable().insertGradient(firstColor, secondColor, firstPosition, secondPosition);

    
}

void setEasyRandomColorGradient(ActionData& action_data) {

  int firstPosition = getInteger(action_data, "First position? ");
  int secondPosition = getInteger(action_data, "Second position? ");

  action_data.getTable().insertEasyRandomGradient(firstPosition, secondPosition);

}


void applyGridColorTable(ActionData& action_data) {

    PPM outputImg = action_data.getOutputImage();

    action_data.getGrid().setPPM(outputImg, action_data.getTable());
    action_data.getOutputImage() = outputImg;
} 

void setFractalPlaneSize(ActionData& action_data) {

    // use dynamic cast here
    NumberGrid *numGrid = &action_data.getGrid(); 
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

void calculateFractal(ActionData& action_data) {
    action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData& action_data) {

   NumberGrid *numGrid = &action_data.getGrid(); 
   JuliaSet *juliaSet = dynamic_cast<JuliaSet *>(numGrid);
 
   if (juliaSet != 0) {
      double paramA = getDouble(action_data, "Parameter a? ");
      double paramB = getDouble(action_data, "Parameter b? ");
      juliaSet->setParameters(paramA, paramB);
      return;
   } else {
     action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
     return;
   }  
}



void calculateFractalSingleThread(ActionData& action_data) {

    NumberGrid& grid = action_data.getGrid();
    grid.NumberGrid::calculateAllNumbers();

}


// HSV
void setHueSaturationValueGradient(ActionData& action_data) {
    int firstPosition = getInteger(action_data, "First position? ");
    double firstHue = getDouble(action_data, "First hue? ");
    double firstSat = getDouble(action_data, "First saturation? ");
    double firstValue = getDouble(action_data, "First value? ");
    
    int secondPosition = getInteger(action_data, "Second position? ");
    double secondHue = getDouble(action_data, "Second hue? ");
    double secondSat = getDouble(action_data, "Second saturation? ");
    double secondValue = getDouble(action_data, "Second value? ");
    
    Color c1;
    Color c2;
    c1.setFromHSV(firstHue, firstSat, firstValue);
    c2.setFromHSV(secondHue, secondSat, secondValue);
    
    action_data.getTable().insertHueSaturationValueGradient(c1, c2, firstPosition, secondPosition);

}