#include "GlutApp.h"
#include "glut_app.h"
#include "AppData.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mData(height, width) {
}

void GlutApp::setSize(int height, int width) {
  mData.setSize(height, width);
  mData.createFractal();
}

int GlutApp::getHeight() const {
  return mData.getHeight();
}
int GlutApp::getWidth() const {
  return mData.getWidth();
}

void GlutApp::display() {
  if (mData.getInteractionMode() == AppData::IM_FRACTAL) {
    displayOutputImage();
  } 
  if (mData.getInteractionMode() == AppData::IM_COLORTABLE) {
    displayColorTable();
  }
  if (mData.getInteractionMode() == AppData::IM_COLOR1) {
    displayColorTable();
  }
  if (mData.getInteractionMode() == AppData::IM_COLOR2) {
    displayColorTable();
  }
  if (mData.getInteractionMode() == AppData::IM_COLOR3) {
    displayColorTable();
  }
}

void GlutApp::displayOutputImage() {
  PPM& p = mData.getOutputImage();
  double max = static_cast<double>(p.getMaxColorValue());
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  for (row = 0; row < p.getHeight(); row++) {
    for (column = 0; column < p.getWidth(); column++) {
      r = p.getChannel(row, column, 0) / max;
      g = p.getChannel(row, column, 1) / max;
      b = p.getChannel(row, column, 2) / max;
      glColor3d(r, g, b);
      glVertex2i(column, p.getHeight()-row-1);
    }
  }
  glEnd( );
}

void GlutApp::displayColorTable() {
  ColorTable& colors = mData.getColorTable();
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  for (row = 0; row < mData.getHeight(); row++) {
    for (column = 0; column < mData.getWidth(); column++) {
      int i = column * colors.getNumberOfColors() / mData.getWidth();
      r = colors[i].getRed() / 255.0;
      g = colors[i].getGreen() / 255.0;
      b = colors[i].getBlue() / 255.0;
      glColor3d(r, g, b); 
      glVertex2i(column, row);
    }
  }
  glEnd( );
}

bool GlutApp::keyboard(unsigned char c) {
  bool post_redisplay = true;

  switch(c) {
    case 'J':
      mData.createJulia1();
      break;
    
    case 'j':
      mData.createJulia2();
      break;
    
    case 'M':
      mData.createMandelbrot1();
      break;

    case 'm':
      mData.createMandelbrot2();
      break;
    
    case 'C':
      mData.createComplexFractal1();
      break;
    
    case 'c':
      mData.createComplexFractal2();
      break;

    case 'T':
      mData.setInteractionMode(AppData::IM_COLORTABLE); 
      break;       
    
    case 't':
      mData.setInteractionMode(AppData::IM_FRACTAL); 
      break;     
    
    case 'b':
      mData.setFractalMode(AppData::M_MANDELBROT);
      mData.createFractal();
      break;    
    
    case 'n':
      mData.setFractalMode(AppData::M_JULIA);
      mData.createFractal();
      break;    
    
    case 'F':
      mData.setFractalMode(AppData::M_COMPLEX);
      mData.createFractal();
      break;    

    case '>':
      mData.increaseColorTableSize();
      break;    
    
    case '.':
      mData.increaseColorTableSize();
      break;    
    
    case '<':
      mData.decreaseColorTableSize();
      break;    
    
    case ',':
      mData.decreaseColorTableSize();
      break;    
    
    case 'r':

      if (mData.getInteractionMode() == AppData::IM_COLORTABLE) {
        mData.randomColor1();
      } 
      break;
    
    case 'R': 
      if (mData.getInteractionMode() == AppData::IM_FRACTAL) {
        mData.resetPlane();
        mData.createFractal();
      } else {
        mData.randomColor2();
      }
      break;
      

    case 'z':
      mData.zoomIn();
      mData.createFractal();
      break;    

    case 'Z':
      mData.zoomOut();
      mData.createFractal();
      break;    

    case '+':
      mData.increaseMaxNumber();
      mData.createFractal();
      break;    
    
    case '=':
      mData.increaseMaxNumber();
      mData.createFractal();   
      break;    
    
    case '-':
      mData.decreaseMaxNumber();
      mData.createFractal();
      break;    
    
    case '_':
      mData.decreaseMaxNumber();
      mData.createFractal();
      break;    

    case '0':
    if (mData.getColorTableMode() == AppData::CT_RANDOM) {
      mData.setAllRandomColors();
      break;
    }
    if (mData.getColorTableMode() == AppData::CT_RANDOM3) {
      mData.set3RandomColors();
      break;
    } else {
      mData.setReverseGradient();
      break;
    } 

    case '1':
        mData.setInteractionMode(AppData::IM_COLOR1);
        break;
      
    case '2':
        mData.setInteractionMode(AppData::IM_COLOR2);
        break;

    case 'Y':
        mData.increaseRed();
        break;
    
    case 'y':
      mData.decreaseRed();
      break;

    case 'U':
      mData.increaseGreen();
      break;

    case 'u':
      mData.decreaseGreen();
      break;

    case 'I':
      mData.increaseBlue();
      break;

    case 'i':
      mData.decreaseBlue();
      break;

    case 'e':
      mData.randomColor3();
      break;
      
    case '3':
      mData.setInteractionMode(AppData::IM_COLOR3);
      break;

    case 'w':
      mData.writeImage();
      break;

    case 'h':
      mData.toggleHSVColor();
      break;
      
    
    default:
      post_redisplay = false;
      break;
  }  
  return post_redisplay;
}

bool GlutApp::special(unsigned char c) {
 bool post_redisplay = true;

  switch(c) {
    case GLUT_KEY_LEFT:
      mData.moveLeft();
      mData.createFractal();
      break;
    
    case GLUT_KEY_RIGHT:
      mData.moveRight();
      mData.createFractal();
      break;

    case GLUT_KEY_DOWN:
      mData.moveDown();
      mData.createFractal();
      break;

    case GLUT_KEY_UP:
      mData.moveUp();
      mData.createFractal();
      break;
    
    default:
      post_redisplay = false;
      break;
  }  
  return post_redisplay;
}



bool GlutApp::mouse(int mouse_button, int state, int x, int y) {
  int xdisplay = x;
  int ydisplay = mData.getHeight() - y;
  bool post_redisplay = false;

  if (mData.getInteractionMode() == AppData::IM_FRACTAL && mData.getFractalMode() == AppData::M_MANDELBROT) {
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mData.setAB(xdisplay, ydisplay);
        mData.setFractalMode(AppData::M_JULIA);
        mData.createFractal();
        post_redisplay = true;
  }
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)  {
      post_redisplay = false;
    }
  if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    mData.zoomOut();
    mData.createFractal();
    post_redisplay = true;
  }

  }
  return post_redisplay;
}
