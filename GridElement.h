#ifndef GRID_ELEMENT
#define GRID_ELEMENT

#include <iostream>

class GridElement {
 public:
    char value;
    int neighbors;

    //default constructor
    GridElement(): value('-'), neighbors(0) {};

    //constructor
    GridElement(char value, int neigbors): value(value), neighbors(neighbors) {};
};

#endif