#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include <iostream>
#include <string>



int assignment1( std::istream& is, std::ostream& os );

// ascii
void drawAsciiImage(ActionData& action_data);
void diagonalQuadPattern( ActionData& action_data );
int assignment2( std::istream& is, std::ostream& os );

// image file
void writeUserImage( ActionData& action_data ) ;
void stripedDiagonalPattern( ActionData& action_data );
int assignment3( std::istream& is, std::ostream& os );


// action & ppm menu
std::string getString( ActionData& action_data, const std::string& prompt );
int getInteger( ActionData& action_data, const std::string& prompt );
double getDouble( ActionData& action_data, const std::string& prompt );
int askQuestions3(ActionData& action_data);
std::string getChoice( ActionData& action_data );
void commentLine( ActionData& action_data );
void quit(ActionData& action_data);
void setSize( ActionData& action_data );
void setMaxColorValue( ActionData& action_data );
void setChannel( ActionData& action_data );
void setPixel( ActionData& action_data );
void clearAll( ActionData& action_data );
void copyImage(ActionData& action_data);
void readUserImage1( ActionData& action_data );

// controllers.cpp new functions from ppm_menu
void showMenu( MenuData& menu_data, ActionData& action_data );
void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data);
void configureMenu( MenuData& menu_data );
int imageMenu(std::istream& is, std::ostream& os);


// ppm operators
void plusEquals( ActionData& action_data );
void minusEquals( ActionData& action_data );
void timesEquals( ActionData& action_data );
void divideEquals( ActionData& action_data );
void plus( ActionData& action_data );
void minus( ActionData& action_data );
void times( ActionData& action_data );
void divide( ActionData& action_data );

void readUserImage2( ActionData& action_data ); 

// image file
void grayFromRed(ActionData& action_data);
void grayFromGreen(ActionData& action_data); 
void grayFromBlue(ActionData& action_data);
void grayFromLinearColorimetric(ActionData& action_data);
void drawCircle(ActionData& action_data); 
void drawBox(ActionData& action_data);
 

 // Number Grid
void configureGrid(ActionData& action_data);
void setGrid(ActionData& action_data);
void applyGrid(ActionData& action_data);


// Color Table
void setColorTableSize(ActionData& action_data);
void setColor(ActionData& action_data);
void setRandomColor(ActionData& action_data);
void setColorGradient(ActionData& action_data);
void applyGridColorTable(ActionData& action_data);

// Complex Fractal
void setFractalPlaneSize(ActionData& action_data);
void calculateFractal(ActionData& action_data);

// Julia Set
void setJuliaParameters(ActionData& action_data);
void setComplexFractal( ActionData& action_data );
void setJuliaFractal( ActionData& action_data );

// Mandelbrot Set
void setMandelbrotFractal( ActionData& action_data );



void setEasyRandomColorGradient(ActionData& action_data);
void setJuliaFourFractal(ActionData& action_data);


// Threaded Grid
void calculateFractalSingleThread(ActionData& action_data);

// HSV
void setHueSaturationValueGradient(ActionData& action_data);
