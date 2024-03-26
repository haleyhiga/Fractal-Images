#include "image_menu.h"
#include "ActionData.h"
#include "MenuData.h"
#include <iostream>
#include <string>


std::string getString( ActionData& action_data, const std::string& prompt ) {
    std::string choice;
    action_data.getOS() << prompt;
    action_data.getIS() >> choice;
    return choice;
}

int getInteger( ActionData& action_data, const std::string& prompt ) {
    int num;
    action_data.getOS() << prompt;
    action_data.getIS() >> num;
    return num;
}


double getDouble( ActionData& action_data, const std::string& prompt ) {
    double decimal;
    action_data.getOS() << prompt;
    action_data.getIS() >> decimal;
    return decimal;
}


int askQuestions3(ActionData& action_data) {
    std::string color = getString(action_data, "What is your favorite color? ");
    int num  = getInteger(action_data, "What is your favorite integer? ");
    double decimal = getDouble(action_data, "What is your favorite number? ");
    if (num <= 0) {
       return num; 
    } else {
    for (int a = 0; a < num; a++) {
        action_data.getOS() << (a + 1) << " " << color << " " << decimal << "\n";
    }
    return num;
    }
}

std::string getChoice( ActionData& action_data ) {
    std::string choice = getString(action_data, "Choice? ");
    return choice;
}


void commentLine( ActionData& action_data ) {
     unsigned char c;

    action_data.getIS().read((char *) &c, sizeof(c));

     while (action_data.getIS().good() && (c != '\n')) {
        action_data.getIS().read((char *) &c, sizeof(c));
    }

}


void quit(ActionData& action_data) {
    // set actiondata to be done
    action_data.setDone();
}

