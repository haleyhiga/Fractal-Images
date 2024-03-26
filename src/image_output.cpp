#include "Image.h"
#include "ActionData.h"
#include "image_menu.h"
#include "PPM.h"
#include <iostream>
#include <string>
#include <fstream>

void drawAsciiImage(ActionData& action_data) {
    
    int row, column;
    int redvalue, bluevalue, greenvalue;
 
    
    for( row = 0; row < action_data.getOutputImage().getHeight(); row ++ ) {

        for( column = 0; column < action_data.getOutputImage().getWidth(); column ++ ) {
            redvalue = action_data.getOutputImage().getChannel(row, column, 0 );
            bluevalue = action_data.getOutputImage().getChannel(row, column, 2 );
            greenvalue = action_data.getOutputImage().getChannel(row, column, 1 );
            double strength = (redvalue + greenvalue + bluevalue) / 765.0;
            if (strength >= 1.0) {
                action_data.getOS() << "@";
            }
            else if (strength >= 0.9) {
        action_data.getOS() << "#";
    }
    else if (strength >= 0.8) {
        action_data.getOS() << "%";
    }
    else if (strength >= 0.7) {
        action_data.getOS() << "*";
    }
    else if (strength >= 0.6) {
        action_data.getOS() << "|";
    }
    else if (strength >= 0.5) {
        action_data.getOS() << "+";
    }
    else if (strength >= 0.4) {
        action_data.getOS() << ";";
    }
    else if (strength >= 0.3) {
        action_data.getOS() << "~";
    }
    else if (strength >= 0.2) {
        action_data.getOS() << "-";
    }
    else if (strength >= 0.1) {
        action_data.getOS() << ".";
    }
    else if (strength >= 0.0) {
        action_data.getOS() << " ";
    }
            
    }

        action_data.getOS() << std::endl;
        }
}



void writeUserImage( ActionData& action_data ) {
    std::string output = getString(action_data, "Output filename? ");
    std::ofstream file(output);
    action_data.getOutputImage().writeStream(file);
    file.close();
}


void copyImage(ActionData& action_data) {
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data ) {
    
    std::string input = getString(action_data, "Input filename? ");
    
    std::ifstream file(input, std::ios::in);

    if (file.is_open()) {
     action_data.getInputImage1().readStream(file);
    } else {
        action_data.getOS() << "'" << input << "' could not be opened.";
    }
    file.close();

}

 void readUserImage2( ActionData& action_data ) {
    
    std::string input = getString(action_data, "Input filename? ");
    
    std::ifstream file(input, std::ios::in);

    if (file.is_open()) {
     action_data.getInputImage2().readStream(file);
    } else {
        action_data.getOS() << "'" << input << "' could not be opened.";
    }
    file.close();
} 
