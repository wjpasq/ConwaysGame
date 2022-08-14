#include <iostream>
#include <tuple>
#include <vector>
#include <limits>
#include "ConwayGrid.h"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "Hello and welcome to Conway's Game of Life!!" << endl << endl;
    cout << "Conway's game starts with a grid of cells, some cells are alive (represented by '*')"
      << " and other cells are dead (represented by '-'). The initial generation is randomly"
      << " generated but every subsequent generation is based on the following rules:" << endl;
    cout << "1. Any live cell with fewer than two live neighbors dies as if caused by"
      << " underpopulation." << endl;
    cout << "2. Any live cell with two or three live neighbors lives on to the next generation." 
      << endl;
    cout << "3. Any live cell with more than three live neighbors dies, as if by overpopulation."
      << endl;
    cout << "4. Any dead cell with exactly three live neighbors becomes a live cell, as if by"
      << " reproduction." << endl << endl;
    
    char quit_char = 'c';

    while (quit_char != 'n' && quit_char != 'N') {
        cout << "Please enter the dimension of the grid (only 1 integer since this is a square"
         << " grid) :: ";
        
        //Get the dimension of the grid
        int size;
        cin >> size;
        while (size < 1) {
            if (cin.fail()) {
                //clear fail state
                cin.clear();

                //get rid of bad characters
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Please enter an integer greater than zero :: ";
            cin >> size;
        }

        //Get the initial number of alive cells
        cout << "Please enter the number of cells you want to be alive in generation 1 :: ";
        int numAlive;
        cin >> numAlive;
        while (numAlive < 1 || numAlive > (size * size)) {
            if (cin.fail()) {
                //clear fail state
                cin.clear();

                //get rid of bad characters
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Please enter an integer greater than zero but less than " << 
                (numAlive * numAlive) << " :: ";
            cin >> numAlive;
        }

        //Generate the grid
        ConwayGrid grid(size, numAlive);
        int gen_num = 1;
        
        cout << endl << "Generation " << gen_num << ": " << endl;
        cout << grid << endl;

        char continue_char;
        cout << "Advance to the next generation? (y/n) :: ";
        string cont_str;
        cin >> cont_str;
        continue_char = cont_str.at(0);

        //clear and flush cin
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (continue_char != 'n' && continue_char != 'N') {
            grid.nextGeneration();
            cout << endl << "Generation " << ++gen_num << ": " << endl;
            cout << grid;
            cout << "There is/are " << grid.numAlive() << " cell(s) left alive." << endl << endl; 

            if (grid.numAlive() > 0) {
                cout << "Advance to the next generation? (y/n) :: ";
                string cont_str;
                cin >> cont_str;
                continue_char = cont_str.at(0);

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Oh No! All the cells are dead :(. They lasted a happy " << (gen_num - 1) << 
                  " generation(s)." << endl;
                break;
            }
        }

        cout << "Do you want to play again? (y/n) :: ";
        string quit_str;
        cin >> quit_str;
        quit_char = quit_str.at(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    
    return 0;
}