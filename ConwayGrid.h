#ifndef CONWAY_H
#define CONWAY_H

#include <iostream>
#include "GridElement.h"

class ConwayGrid {
    //dimension of grid
    int _size;
    //number of tiles alive in the beginning
    int _numAlive;
    GridElement** grid;

 public:
    //constructor
    ConwayGrid(int size, int numAlive);
    //destructor
    ~ConwayGrid();

    void nextGeneration();

    int size() const;

    char at(int row, int col) const;

    int numAlive() const { return this->_numAlive; };
 
 private:
    //Helper functions
    void incrementNeighbors(int row, int col);
    void decrementNeigbors(int row, int col);
};

//override << operatorS
std::ostream& operator<<(std::ostream& os, const ConwayGrid& grid);

#endif