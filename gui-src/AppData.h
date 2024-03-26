#ifndef _APPDATA_H_
#define _APPDATA_H_

#include "ActionData.h"
#include "MenuData.h"

#include <sstream>

class AppData {


public:

  enum InteractionMode { IM_FRACTAL, IM_COLORTABLE, IM_COLOR1, IM_COLOR2, IM_COLOR3 };
  enum FractalMode { M_MANDELBROT, M_JULIA, M_COMPLEX };
  
  //practice exam
  enum ColorTableMode { CT_GRADIENT, CT_RANDOM3, CT_RANDOM, CT_REVERSE};
  void nextColorTableMode();
  ColorTableMode getColorTableMode() const;
  void set3RandomColors();
  void setAllRandomColors();
  void setReverseGradient();


  // exam
  void increaseChannel(Color& color, int channel);
  void decreaseChannel(Color& color, int channel);
  Color& fetchColor();
  void increaseRed();
  void decreaseRed();
  void increaseGreen();
  void decreaseGreen();
  void increaseBlue();
  void decreaseBlue();
  void randomColor3();

  void writeImage();


  AppData(int height, int width); // constructor
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;

  PPM& getOutputImage();
  ColorTable& getColorTable();
  
  // Interesting pre-configured set images
  void createJulia1();
  void createJulia2();
  void createMandelbrot1();
  void createMandelbrot2();
  void createComplexFractal1(); 
  void createComplexFractal2();

  void clearStreams();
  
  // Run Command Methods
  void runCommand(const std::string& choice);
  void selectJulia();
  void selectMandelbrot();
  void selectComplexFractal();
  void configureGrid(int max); 
  void juliaParameters(double a, double b);
  void fractalPlaneSize(double x_min, double x_max, double y_min, double y_max);
  void fractalCalculate();
  void gridApplyColorTable();

  // Interaction Modes
  void setInteractionMode(InteractionMode mode);
  InteractionMode getInteractionMode() const;

  // Color Table stuff
  void setColorTable();
 
  void decreaseColorTableSize();
  void increaseColorTableSize(); 
  void randomColor1();
  void randomColor2();

  // Complex Fractal stuff
  void zoomIn();
  void zoomOut();
  void moveLeft();
  void moveRight(); 
  void moveDown();
  void moveUp();

  void setFractalMode(FractalMode mode);
  FractalMode getFractalMode() const;

  // Julia Set stuff
  void increaseMaxNumber();
  void decreaseMaxNumber();


  void setAB(int x, int y);
  void resetPlane();
  void createFractal();

  // HSV
  void toggleHSVColor();



protected:
  int mHeight, mWidth;
  int mMaxNumber;
  InteractionMode mInteractionMode;
  FractalMode mFractalMode;
  int mNumColor;
  Color mColor1; 
  Color mColor2;



  double mMinX;
  double mMaxX;
  double mMinY;
  double mMaxY;
  double mA;
  double mB;
  std::stringstream mInputStream; 
  std::stringstream mOutputStream; 
  ActionData mActionData;
  MenuData mMenuData;
  int mDebug;

  // practice exam
  ColorTableMode mColorTableMode;

  //exam
  Color mColor3;
  int mImageNumber;

  //final
  bool mHSVColor;
  
};

#endif /* _APPDATA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */