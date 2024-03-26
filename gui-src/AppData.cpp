#include "AppData.h"
#include "image_menu.h"
#include <iostream>

AppData::AppData(int height, int width) 
  : mHeight(height), mWidth(width), mMaxNumber(255), mInteractionMode(IM_FRACTAL), mFractalMode(M_JULIA), mNumColor(100),
  mColor1(255, 51, 153), mColor2(102, 102, 255), mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0), mA(-0.7269), mB(0.1889),
  mActionData(mInputStream, mOutputStream), mDebug(1), mColorTableMode(CT_GRADIENT), mColor3(255, 51, 153), mImageNumber(1), mHSVColor(false)

  
   {

    // interesting numbers for julia set from: https://en.wikipedia.org/wiki/Julia_set
     

     configureMenu(mMenuData);
     mActionData.setGrid(new ComplexFractal);

     setColorTable();
     createFractal();

}

void AppData::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int AppData::getHeight() const {
  return mHeight;
}

int AppData::getWidth() const {
  return mWidth;
}

PPM& AppData::getOutputImage() {
  return mActionData.getOutputImage();
}

ColorTable& AppData::getColorTable() {
  return mActionData.getTable();
}

void AppData::createJulia1() {

  // julia
  selectJulia(); // runs takeAction julia command

  // grid
  configureGrid(200); 

  // julia parameters
  juliaParameters(-0.8, 0.156);

  // fractal plane size
  fractalPlaneSize(-2.0, 2.0, -2.0, 2.0); 

  fractalCalculate();
  
  // sets colors and color table size and gradient
  mColor1 = Color(0, 204, 102);
  mColor2 = Color(0, 255, 255);
  
  setColorTable(); 

  gridApplyColorTable();

}

// choose different interesting values
void AppData::createJulia2() {

  // julia
  selectJulia(); // runs takeAction julia command

  // grid
  configureGrid(200); 

  // julia parameters
  juliaParameters(-0.4, 0.6);

  // fractal plane size
  fractalPlaneSize(-2.0, 2.0, -2.0, 2.0); 

  fractalCalculate();

  // changes the colors
  mColor1 = Color(255, 0, 0);
  mColor2 = Color(255, 128, 0);

  setColorTable(); 

  gridApplyColorTable();

}


void AppData::createMandelbrot1() {

    selectMandelbrot();

    configureGrid(200);
    
    fractalPlaneSize(-1.7, 2.0, -1.7, 2.0); 

    fractalCalculate();
  
    // sets color table size and gradient
    mColor1 = Color(0, 204, 204);
    mColor2 = Color(0, 102, 204);

    setColorTable();

    gridApplyColorTable();

}

// change plane size for different mandelbrot
void AppData::createMandelbrot2() {
    
    selectMandelbrot();

    configureGrid(200);
    
    fractalPlaneSize(-1.5, 1.0, -1.5, 1.0);  // change the plane size to generate a different mandelbrot

    fractalCalculate();
  
    // sets color table size and gradient
    mColor1 = Color(51, 153, 255);
    mColor2 = Color(51, 51, 255);

    setColorTable();

    gridApplyColorTable();
}

void AppData::createComplexFractal1() {
    
    selectComplexFractal();

    configureGrid(200);
    
    fractalPlaneSize(-1.0, 1.3, -1.0, 1.3);

    fractalCalculate();
  
    // sets color table size and gradient
    mColor1 = Color(255, 51, 153);
    mColor2 = Color(255, 51, 255);


      setColorTable();

    gridApplyColorTable();

}

void AppData::createComplexFractal2() {
    
    selectComplexFractal();

    configureGrid(200);
    
    fractalPlaneSize(-0.77, 1.2, -0.77, 1.2);

    fractalCalculate();
 
    // sets color table size and gradient
    mColor1 = Color(0, 255, 0);
    mColor2 = Color(255, 255, 0);
      
      setColorTable();

      gridApplyColorTable();
}

void AppData::clearStreams() {
  mInputStream.clear();
  mInputStream.str("");
  mOutputStream.clear();
  mOutputStream.str("");
}

void AppData::runCommand(const std::string& choice) {
    
    if (mDebug != 0) {
      std::cout << choice << " " << mInputStream.str() << std::endl;
      takeAction(choice, mMenuData, mActionData);
      std::cout << mOutputStream.str() << std::endl; // uses stringstream
    } else {
      takeAction(choice, mMenuData, mActionData);
    }
}

void AppData::selectJulia() {

  clearStreams();
  setFractalMode(M_JULIA);
  runCommand("julia");

}

void AppData::selectMandelbrot() {
  
  clearStreams();
  setFractalMode(M_MANDELBROT);
  runCommand("mandelbrot");

}

void AppData::selectComplexFractal() {

  clearStreams();
  setFractalMode(M_COMPLEX);
  runCommand("complex-fractal");

}

void AppData::configureGrid(int max) {

  clearStreams(); 
  {
    std::stringstream tmp;
    tmp << mHeight << " " << mWidth << " " << max;
    mInputStream.str(tmp.str());
  }
  //takeAction("grid", mMenuData, mActionData);
  runCommand("grid");
}

void AppData::juliaParameters(double a, double b) {
  
  clearStreams(); 
  {
    std::stringstream tmp;
    tmp << a << " " << b;
    mInputStream.str(tmp.str());
  }
  //takeAction("julia-parameters", mMenuData, mActionData);
  runCommand("julia-parameters");
}

void AppData::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {

  clearStreams(); 
  {
    std::stringstream tmp;
    tmp << x_min << " " << x_max << " " << y_min << " " << y_max;
    mInputStream.str(tmp.str());
  }
  //takeAction("fractal-plane-size", mMenuData, mActionData);
  runCommand("fractal-plane-size");
}

void AppData::fractalCalculate() {

  clearStreams();
  //takeAction("fractal-calculate", mMenuData, mActionData);
  runCommand("fractal-calculate");
}

void AppData::gridApplyColorTable() {

  clearStreams();
  //takeAction("grid-apply-color-table", mMenuData, mActionData);  // instead we use runcommand
  runCommand("grid-apply-color-table");
}

void AppData::setInteractionMode(InteractionMode mode) {
  mInteractionMode = mode;
}

AppData::InteractionMode AppData::getInteractionMode() const {
  return mInteractionMode;
}

void AppData::setColorTable() {

   // set-color-table-size
   clearStreams(); 
  {
    std::stringstream tmp;
    tmp << mNumColor;
    mInputStream.str(tmp.str());
  }
  runCommand("set-color-table-size");


if (!mHSVColor) {
  // set-color-gradient (added for the exam)
  clearStreams(); 
  {
    std::stringstream tmp;
    // First position? First red? First Green?  First Blue?  Last Position?  Second red?  Second green?  Second blue?
    tmp << 0 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " " << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue();
    mInputStream.str(tmp.str());
  }
  runCommand("set-color-gradient");

  clearStreams(); 
  {
    std::stringstream tmp;
    // First position? First red? First Green?  First Blue?  Last Position?  Second red?  Second green?  Second blue?
    tmp << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue() << " " << mNumColor-1 << " " << mColor3.getRed() << " " << mColor3.getGreen() << " " << mColor3.getBlue();
    mInputStream.str(tmp.str());
  }
  runCommand("set-color-gradient");
} else {
  // do hsv
  double hue1, sat1, value1;
  double hue2, sat2, value2;


  mColor1.getHSV(hue1, sat1, value1);
  mColor2.getHSV(hue2, sat2, value2);
  


  clearStreams(); 
  {
    std::stringstream tmp;
    // First position? First red? First Green?  First Blue?  Last Position?  Second red?  Second green?  Second blue?
    tmp << 0 << " " << hue1 << " " << sat1 << " " << value1 << " " << mNumColor-1 << " " << hue2 << " " << sat2 << " " << value2;
    mInputStream.str(tmp.str());
  }
  runCommand("set-hsv-gradient");

}



  if (mColorTableMode == CT_RANDOM3) {
    set3RandomColors();
  }
  if (mColorTableMode == CT_RANDOM) {
    setAllRandomColors();
  } 
  if (mColorTableMode == CT_REVERSE) {
    setReverseGradient();
  }

}


void AppData::decreaseColorTableSize() {

  if (mNumColor > 10) {
    double newNumColor = mNumColor / 1.1;
    mNumColor = newNumColor;
    setColorTable();
    gridApplyColorTable();
  }
}

void AppData::increaseColorTableSize() {

  if (mNumColor < 1024) {
    mNumColor *= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void AppData::randomColor1() {

  PPM& p = mActionData.getOutputImage();
  int maxColorValue = p.getMaxColorValue();

  mColor1.setRed(rand() % (maxColorValue + 1));  // added one to make it inclusive
  mColor1.setGreen(rand() % (maxColorValue + 1));
  mColor1.setBlue(rand() % (maxColorValue + 1));

  setColorTable();
  gridApplyColorTable();
}

void AppData::randomColor2() {

  PPM& p = mActionData.getOutputImage();
  int maxColorValue = p.getMaxColorValue();

  mColor2.setRed(rand() % (maxColorValue + 1));  // added one to make it inclusive
  mColor2.setGreen(rand() % (maxColorValue + 1));
  mColor2.setBlue(rand() % (maxColorValue + 1));

  setColorTable();
  gridApplyColorTable();
}




void AppData::zoomIn() {

    double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
    mMinX += dx;
    mMaxX -= dx;

    double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
    mMinY += dy;
    mMaxY -= dy;
  }

void AppData::zoomOut() {

  if (mMinX >= -2.0 && mMinX <= 2.0 && mMaxX >= -2.0 && mMaxX <= 2.0 && mMinY >= -2.0 && mMinY <= 2.0 && mMaxY >= -2.0 && mMaxY <= 2.0) {
   double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
   mMinX -= dx;
   mMaxX += dx;

   double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
   mMinY -= dy;
   mMaxY += dy;
  }
}

void AppData::moveLeft() {

  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  if ((mMinX - dx) >= -2.0) {
    mMinX -= dx;
    mMaxX -= dx;
  }
}

void AppData::moveRight() {

  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  if ((mMinX - dx) >= -2.0) {
    mMinX += dx;
    mMaxX += dx;
  }
}

void AppData::moveDown() {

  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  if ((mMinY - dy) >= -2.0) {
    mMinY -= dy;
    mMaxY -= dy;
  }
}

void AppData::moveUp() {

  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  if ((mMinY - dy) >= -2.0) {
    mMinY += dy;
    mMaxY += dy;
  }
}

void AppData::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
}

AppData::FractalMode AppData::getFractalMode() const {
  return mFractalMode;
}

void AppData::increaseMaxNumber() {
  
  if (mMaxNumber < 2048) {
    mMaxNumber = mMaxNumber * 1.1;
  }
}

void AppData::decreaseMaxNumber() {
  
  if (mMaxNumber > 11) {
    mMaxNumber = mMaxNumber / 1.1;
  }
}


void AppData::setAB(int x, int y) {
    
    ComplexFractal *complexFrac = dynamic_cast<ComplexFractal *>(&mActionData.getGrid());
  
  if ( mFractalMode == M_MANDELBROT && complexFrac != 0 ) {    // check if mActionData grid is a ComplexFractal object
      // delta_x is obtained from the dynamically cast complexfractal pointer with getDeltaX()
      mA = mMinX + x * complexFrac->getDeltaX();
      mB = mMinY + y * complexFrac->getDeltaY();
  }
}

void AppData::resetPlane() {
  mMinX = -2.0;
  mMinY = -2.0;
  mMaxX = 2.0;
  mMaxY = 2.0;
}

void AppData::createFractal() {
  
  if (mFractalMode == M_MANDELBROT) {
    selectMandelbrot();
  }
  if (mFractalMode == M_JULIA) {
    selectJulia();
    juliaParameters(mA, mB);
  }
  if (mFractalMode == M_COMPLEX) {
    selectComplexFractal();
  }
  configureGrid(mMaxNumber);
  fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
  fractalCalculate();
  gridApplyColorTable();
}


//practice exam
void AppData::nextColorTableMode() {
  if (mColorTableMode == CT_GRADIENT) {
    mColorTableMode = CT_RANDOM3;
  }

  if (mColorTableMode == CT_RANDOM3) {
    mColorTableMode = CT_RANDOM;
  }
  if (mColorTableMode == CT_RANDOM) {
    mColorTableMode = CT_REVERSE;
  }
  if (mColorTableMode == CT_REVERSE) {
    mColorTableMode = CT_GRADIENT;
  }
  setColorTable();
  gridApplyColorTable();

}

AppData::ColorTableMode AppData::getColorTableMode() const {
  return mColorTableMode;
}

void AppData::set3RandomColors() {

  clearStreams(); 
  {
    std::stringstream tmp;
    tmp << 0;
    mInputStream.str(tmp.str());
  }
  runCommand("set-random-color");

    clearStreams(); 
  {
    std::stringstream tmp;
    tmp << mNumColor/2;
    mInputStream.str(tmp.str());
  }
  runCommand("set-random-color");

  clearStreams(); 
  {
    std::stringstream tmp;
    tmp << mNumColor-1;
    mInputStream.str(tmp.str());
  }
  runCommand("set-random-color");

} 

void AppData::setAllRandomColors() {

  for (int position = 0; position <= mNumColor; position++) {
  clearStreams(); 
  {
    std::stringstream tmp;
    tmp << position;
    mInputStream.str(tmp.str());
  }
  runCommand("set-random-color");
}
}

void AppData::setReverseGradient() {
    clearStreams(); 
  {
    std::stringstream tmp;
    // First position? First red? First Green?  First Blue?  Last Position?  Second red?  Second green?  Second blue?
    tmp << 0 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " " << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue();
    mInputStream.str(tmp.str());
  }
  runCommand("set-color-gradient");

    clearStreams(); 
  {
    std::stringstream tmp;
    // First position? First red? First Green?  First Blue?  Last Position?  Second red?  Second green?  Second blue?
    tmp << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue() << " " << mNumColor-1 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue();
    mInputStream.str(tmp.str());
  }
  runCommand("set-color-gradient");
}

void AppData::increaseChannel(Color& color, int channel) {
  int red = color.getRed();
  int green = color.getGreen();
  int blue = color.getBlue();

  if (channel == 0) {
    red += 10;
    if (red > 255) {
      color.setRed(255);
    } else {
      color.setRed(red);
    }
  }

  if (channel == 1) {
    green += 10;
    if (green > 255) {
      color.setGreen(255);
    } else {
      color.setGreen(green);
    }
  }

    if (channel == 2) {
    blue += 10;
    if (blue > 255) {
      color.setBlue(255);
    } else {
      color.setBlue(blue);
    }
  }
  setColorTable();
  gridApplyColorTable();
}


void AppData::decreaseChannel(Color& color, int channel) {
  int red = color.getRed();
  int green = color.getGreen();
  int blue = color.getBlue();

  if (channel == 0) {
    red -= 10;
    if (red < 0) {
      color.setRed(0);
    } else {
      color.setRed(red);
    }
  }

  if (channel == 1) {
    green -= 10;
    if (green < 0) {
      color.setGreen(0);
    } else {
      color.setGreen(green);
    }
  }

    if (channel == 2) {
    blue -= 10;
    if (blue < 0) {
      color.setBlue(0);
    } else {
      color.setBlue(blue);
    }
  }
  setColorTable();
  gridApplyColorTable();
}

Color& AppData::fetchColor() {
  if (getInteractionMode() == IM_COLOR1) {
    return mColor1;
  }
  if (getInteractionMode() == IM_COLOR2) {
    return mColor2;
  } 
  if (getInteractionMode() == IM_COLOR3) {
    return mColor3;
  } else {
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    return c;
  }

}

void AppData::increaseRed() {
  increaseChannel(fetchColor(), 0);
}

void AppData::decreaseRed() {
  decreaseChannel(fetchColor(), 0);
}

void AppData::increaseGreen() {
  increaseChannel(fetchColor(), 1);
}

void AppData::decreaseGreen() {
decreaseChannel(fetchColor(), 1);
}

void AppData::increaseBlue() {
  increaseChannel(fetchColor(), 2);
}

void AppData::decreaseBlue() {
decreaseChannel(fetchColor(), 2);
}

void AppData::randomColor3() {

  PPM& p = mActionData.getOutputImage();
  int maxColorValue = p.getMaxColorValue();

  mColor3.setRed(rand() % (maxColorValue + 1));  // added one to make it inclusive
  mColor3.setGreen(rand() % (maxColorValue + 1));
  mColor3.setBlue(rand() % (maxColorValue + 1));

  setColorTable();
  gridApplyColorTable();
}

void AppData::writeImage() {
  clearStreams();
    {
    std::stringstream tmp;
    tmp << "image-" << mImageNumber << ".ppm";
    mInputStream.str(tmp.str());
  }
  mImageNumber++;
  runCommand("write");

}

void AppData::toggleHSVColor() {
  if (mHSVColor) {
    mHSVColor = true;
  }
  setColorTable();
  gridApplyColorTable();
}