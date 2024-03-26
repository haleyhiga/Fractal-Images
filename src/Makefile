CXXFLAGS := -std=c++11
CXXFLAGS := $(CXXFLAGS) -Wall -Wpedantic -Wextra -Werror
CXXFLAGS := $(CXXFLAGS) -g
LINKFLAGS := $(LINKFLAGS) -lpthread


all: hello questions_3 ascii_image image_file ppm_menu 
#inquisitor simple_squares_ascii four_square buck


#hello
hello: hello.o
	g++ $(CXXFLAGS) -o hello hello.o

hello.o: hello.cpp
	g++ $(CXXFLAGS) -c hello.cpp


#questions_3
questions_3: questions_3.o controllers.o user_io.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS)  -o questions_3 questions_3.o controllers.o user_io.o image_output.o image_drawing.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

questions_3.o: questions_3.cpp image_menu.h
	g++ $(CXXFLAGS) -c  questions_3.cpp

controllers.o: controllers.cpp image_menu.h Image.h PPM.h ActionData.h MenuData.h
	g++ $(CXXFLAGS) -c  controllers.cpp

user_io.o: user_io.cpp image_menu.h ActionData.h 
	g++ $(CXXFLAGS) -c  user_io.cpp


#ascii image
ascii_image: ascii_image.o controllers.o image_output.o image_drawing.o Image.o user_io.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS) -o ascii_image ascii_image.o controllers.o image_output.o image_drawing.o Image.o user_io.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

ascii_image.o: ascii_image.cpp Image.h image_menu.h
	g++ $(CXXFLAGS)  -c ascii_image.cpp

image_drawing.o: image_drawing.cpp Image.h image_menu.h ActionData.h
	g++ $(CXXFLAGS)  -c image_drawing.cpp

image_output.o: image_output.cpp Image.h image_menu.h ActionData.o
	g++ $(CXXFLAGS)  -c image_output.cpp

Image.o: Image.cpp Image.h
	g++ $(CXXFLAGS)  -c Image.cpp


#image_file
image_file: image_file.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS)  -o image_file image_file.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

image_file.o: image_file.cpp image_menu.h Image.h PPM.h 
	g++ $(CXXFLAGS)  -c image_file.cpp

PPM.o: PPM.cpp PPM.h Image.h
	g++ $(CXXFLAGS)  -c PPM.cpp


#inquisitor
#inquisitor: inquisitor.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o
#	g++ $(CXXFLAGS) -o inquisitor inquisitor.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o

#inquisitor.o: inquisitor.cpp PPM.h Image.h
#	g++ $(CXXFLAGS) -c inquisitor.cpp


# ascii squares
#simple_squares_ascii: simple_squares_ascii.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o
#	g++ $(CXXFLAGS) -o simple_squares_ascii simple_squares_ascii.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o

#simple_squares_ascii.o: simple_squares_ascii.cpp image_menu.h Image.h
#	g++ $(CXXFLAGS) -c simple_squares_ascii.cpp


# four squares
#four_square: four_square.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o
#	g++ $(CXXFLAGS) -o four_square four_square.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o

#our_square.o: four_square.cpp image_menu.h Image.h
#	g++ $(CXXFLAGS) -c four_square.cpp


# buck
#buck: buck.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o
#	g++ $(CXXFLAGS) -o buck buck.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o

#buck.o: buck.cpp PPM.h Image.h
#	g++ $(CXXFLAGS) -c buck.cpp


# columbia
#flag_columbia_ascii: flag_columbia_ascii.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o
#	g++ $(CXXFLAGS) -o flag_columbia_ascii flag_columbia_ascii.o image_output.o image_drawing.o controllers.o user_io.o PPM.o Image.o

#flag_columbia_ascii.o: flag_columbia_ascii.cpp image_menu.h Image.h
#	g++ $(CXXFLAGS) -c flag_columbia_ascii.cpp


# action & menu data

ActionData.o: ActionData.cpp PPM.h ActionData.h MenuData.h
	g++ $(CXXFLAGS)  -c ActionData.cpp

MenuData.o: MenuData.cpp MenuData.h ActionData.h 
	g++ $(CXXFLAGS)  -c MenuData.cpp 

# ppm menu
ppm_menu: ppm_menu.o controllers.o image_output.o image_drawing.o Image.o user_io.o PPM.o MenuData.o ActionData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ $(CXXFLAGS)  -o ppm_menu ppm_menu.o controllers.o image_output.o image_drawing.o Image.o user_io.o PPM.o MenuData.o ActionData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

ppm_menu.o: ppm_menu.cpp image_menu.h ActionData.h MenuData.h
	g++ $(CXXFLAGS) -c ppm_menu.cpp

#ppm operators
image_filters.o: image_filters.cpp image_menu.h
	g++ $(CXXFLAGS) -c image_filters.cpp

# Number Grid
NumberGrid.o: NumberGrid.cpp NumberGrid.h PPM.h
	g++ $(CXXFLAGS) -c NumberGrid.cpp

# Color Table
ColorTable.o: ColorTable.cpp ColorTable.h
	g++ $(CXXFLAGS) -c ColorTable.cpp

# Complex Fractal
ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.cpp NumberGrid.o NumberGrid.h
	g++ $(CXXFLAGS) -c ComplexFractal.cpp

# Julia Set
JuliaSet.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.cpp NumberGrid.o NumberGrid.h JuliaSet.h JuliaSet.cpp
	g++ $(CXXFLAGS) -c JuliaSet.cpp

# Mandelbrot Set
MandelbrotSet.o: ComplexFractal.cpp ComplexFractal.h NumberGrid.cpp NumberGrid.o NumberGrid.h MandelbrotSet.h MandelbrotSet.cpp
	g++ $(CXXFLAGS) -c MandelbrotSet.cpp

# Threaded Grid
ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h NumberGrid.cpp NumberGrid.h
	g++ $(CXXFLAGS) -c ThreadedGrid.cpp

clean:
	-rm -f *.o
