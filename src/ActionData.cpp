#include "ActionData.h"
#include "ColorTable.h"
#include "PPM.h"
#include <iostream>


// constructor
ActionData::ActionData(std::istream& is, std::ostream& os)
    : mIs(is), mOs(os), mDone(false), mNumberGrid( 0 ), mColorTable( 16 ) { 
        mColorTable.insertGradient(Color(0, 255, 0), Color(255, 0, 255), 0, 15); // fills colortable with gradient
        
}

std::istream& ActionData::getIS() { 
    return mIs;
}

std::ostream& ActionData::getOS() {
    return mOs;
}

PPM& ActionData::getInputImage1() {
    return inputImage1;
}

PPM& ActionData::getInputImage2() {
    return inputImage2;
}

PPM& ActionData::getOutputImage() {
    return outputImage;
}

bool ActionData::getDone() const {
    return mDone;
}

void ActionData::setDone() {
    mDone = true;
}

ActionData::~ActionData() {
    if (mNumberGrid != 0) {
        delete mNumberGrid;  // i could also set mNumberGrid = 0 after to double check memory doesn't leak 
    }
}

NumberGrid& ActionData::getGrid() {
    return *mNumberGrid;
}

void ActionData::setGrid(NumberGrid *grid) {
    if (mNumberGrid != 0) {
        delete mNumberGrid;
    }
    mNumberGrid = grid;  // this copies pointers, it does not copy the contents that its pointing to
}

// Color Table
 ColorTable& ActionData::getTable() {
    return mColorTable;
} 



