#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_

#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include <vector>
#include <map>

#include <iostream>

class ActionData: public PPM {

public:

    ActionData(std::istream& is, std::ostream& os);
    std::istream& getIS();
    std::ostream& getOS();
    PPM& getInputImage1();
    PPM& getInputImage2();
    PPM& getOutputImage();
    bool getDone() const;
    void setDone();

    // Number Grid
    ~ActionData();
    NumberGrid& getGrid();
    void setGrid(NumberGrid *grid);

    // Color Table
    ColorTable& getTable(); // returns color table data member


protected:

    std::istream& mIs;
    std::ostream& mOs;
    PPM inputImage1;
    PPM inputImage2;
    PPM outputImage;
    bool mDone;
    NumberGrid *mNumberGrid; // number grid pointer

    ColorTable mColorTable; // a color table object


};

#endif /* _ACTIONDATA_H_ */