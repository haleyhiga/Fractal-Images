#ifndef _THREADEDGRID_H_
#define _THREADEDGRID_H_

#include "NumberGrid.h"
#include <vector>
#include <mutex>

#include <iostream>

// Helper class to help determine row and column in grid.
class Position {

public:
   
    Position();
    Position(const int& height, const int& width);
    virtual ~Position(); // destructor
   
    int mRow;
    int mColumn;

};

class ThreadedGrid: public NumberGrid {

public:
    ThreadedGrid(); // default constructor
    ThreadedGrid(const int& height, const int& width); // constructor
    virtual ~ThreadedGrid(); // destructor
    virtual void calculateAllNumbers(); // overrides NumberGrid calculateAllNumbers
    virtual void worker();  // worker method


protected:

    std::vector<Position> mTaskObjects;
    std::mutex mTaskLock;
};



#endif /* _THREADEDGRID_H_ */