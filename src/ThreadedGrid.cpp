#include "ThreadedGrid.h"
#include <iostream>
#include <thread>

ThreadedGrid::ThreadedGrid()
    : NumberGrid(), mTaskObjects(), mTaskLock() {
    }

ThreadedGrid::ThreadedGrid(const int& height, const int& width)
    : NumberGrid (height, width)  {
    }

ThreadedGrid::~ThreadedGrid() {}  // destructor


// Constructor of helper class
Position::Position()
    : mRow( ), mColumn( ) {
    }

Position::~Position() {} // destructor for helper class


void ThreadedGrid::calculateAllNumbers() {

    Position gridPosition;
    std::vector<std::thread> threads;
   
    // adding to our vector data member
    int row, column;
    for (row=0; row < mHeight; row++) {
        for (column=0; column < mWidth; column++) {
        
           gridPosition.mRow = row;
           gridPosition.mColumn = column;
           mTaskObjects.push_back(gridPosition);

        }
    }

    // operating system will determine how many cores
    unsigned int cores = std::thread::hardware_concurrency();
    unsigned int i;
    for (i = 0; i < cores; i++) {
        threads.push_back(std::thread(&ThreadedGrid::worker, this));
    }
    // waiting for threads to finish
    for(i = 0; i < threads.size(); i++) {
         threads[i].join();
  }
}


void ThreadedGrid::worker() {
    /* As long as tasks are available in the task queue, get one, and complete it. Should use calculateNumber() and setNumber() */

  Position gridPosition;

  while(true) {

    mTaskLock.lock();
    if(mTaskObjects.size() == 0) {  // if no more tasks available, exit loop
      mTaskLock.unlock();
      break; 
    }
    gridPosition = mTaskObjects.back();  // grab object at the end of vector
    mTaskObjects.pop_back();    // pop off object at the end of vector
    mTaskLock.unlock();    // unlock when done
    
    int num = calculateNumber(gridPosition.mRow, gridPosition.mColumn);
    setNumber(gridPosition.mRow, gridPosition.mColumn, num);
  }
}


