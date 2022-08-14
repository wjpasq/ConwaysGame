#include "ConwayGrid.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <time.h>

using namespace std;

ConwayGrid::ConwayGrid(int size, int numAlive) {
    this->_size = size;
    this->_numAlive = numAlive;

    //initialize grid
    this->grid = new GridElement*[size];
    for (int i = 0; i < size; i++) {
        this->grid[i] = new GridElement[size];
    }

    //reservior sampling random select
    GridElement **reservior_ptrs = new GridElement*[numAlive];
    GridElement *grid_ptr;
    for (int i = 0; i < numAlive; i++) {
        int row = i / size;
        int col = i % size;

        grid_ptr = &(this->grid[row][col]);
        reservior_ptrs[i] = grid_ptr;
    }

    srand(time(NULL));

    // iterate from (k+1)th element to nth element
    for (int i = numAlive; i < (size * size); i++) {
        int row = i / size;
        int col = i % size;
        
        //pick random index from 0 to i
        int j = rand() % (i + 1);

        if (j < numAlive) {
            grid_ptr = &(this->grid[row][col]);
            reservior_ptrs[j] = grid_ptr;
        }
    }

    //iterate through reservior and set value to '*'
    for (int i = 0; i < numAlive; i++) {
        reservior_ptrs[i]->value = '*';
    }

    //initialize neighbor values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //check the neighbors
            int neighbors = 0;
            for (int row = i - 1; row <= i + 1; row++) {
                //check if row in bounds
                if (row >= 0 && row < size) {
                    for (int col = j - 1; col <= j + 1; col++) {
                        //check if inbounds
                        if ((col >= 0 && col < size) && !(row == i && col == j)) {
                            if (this->grid[row][col].value == '*') {
                                neighbors++;
                            }
                        }
                    }
                }
            }
            this->grid[i][j].neighbors = neighbors;
        }
    }

    delete[] reservior_ptrs;
}

//destructor
ConwayGrid::~ConwayGrid() {
    for (int i = 0; i < this->_size; i++) {
        delete[] this->grid[i];
    }
    delete[] this->grid;
}

void ConwayGrid::incrementNeighbors(int row, int col) {
    for (int i = row - 1; i <= row + 1; i++) {
        if (i >= 0 && i < this->_size) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (j >= 0 && j < this->_size && !(i == row && j == col)) {
                    this->grid[i][j].neighbors++;
                }
            }
        }
    }
}

void ConwayGrid::decrementNeigbors(int row, int col) {
    for (int i = row - 1; i <= row + 1; i++) {
        if (i >= 0 && i < this->_size) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (j >= 0 && j < this->_size && !(i == row && j == col)) {
                    this->grid[i][j].neighbors--;
                }
            }
        }
    }
}

void ConwayGrid::nextGeneration() {
    //increment tuples
    vector<tuple<int, int>> incPositions;
    vector<tuple<int, int>> decPositions;
    
    for (int i = 0; i < this->_size; i++) {
        for (int j = 0; j < this->_size; j++) {
            bool alive = this->grid[i][j].value == '*';
            int neighbors = this->grid[i][j].neighbors;
            if (!alive && neighbors == 3) {
                this->grid[i][j].value = '*';
                this->_numAlive++;
                incPositions.push_back(make_tuple(i, j));
            } else if (alive && (neighbors < 2 || neighbors > 3)) {
                this->grid[i][j].value = '-';
                this->_numAlive--;
                decPositions.push_back(make_tuple(i, j));
            }
        }
    }

    for (int i = 0; i < incPositions.size(); i++) {
        tuple<int, int> pos = incPositions.at(i);
        this->incrementNeighbors(get<0>(pos), get<1>(pos));
    }

    for (int i = 0; i < decPositions.size(); i++) {
        tuple<int, int> pos = decPositions.at(i);
        this->decrementNeigbors(get<0>(pos), get<1>(pos));
    }
}

int ConwayGrid::size() const {
    return this->_size;
}

char ConwayGrid::at(int row, int col) const {
    return this->grid[row][col].value;
}

std::ostream& operator<<(std::ostream& os, const ConwayGrid& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            os << grid.at(i, j) << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}