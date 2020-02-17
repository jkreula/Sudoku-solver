//
//  sudokuMain.cpp
//  
//
//  Created by Juha Kreula on 23/01/2020.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "sudokuGrid.hpp"
#include "sudokuSolver.hpp"


using std::cout, std::cin, std::endl;


// Overloaded output operator for Grid
std::ostream & operator<<(std::ostream & out, Grid & grid)
{
    std::for_each (grid.array.begin(), grid.array.end(), [&out,&grid](std::vector<int> & row) {
        for (int col=0; col < grid.cols; ++col)
        {
            if (row[col] == 0)
                out << "- ";
            else
                out << row[col] << " ";
        }
        out << std::endl;
    });
    return out;
}

int main(int argc, char* argv[])
{
    
    const int size = 9;
    Grid grid(size);
    
    char ans;
    cout << "Give non-empty Sudoku grid cells on command line? (y/n)" << endl;
    cin >> ans;

    if( std::tolower(ans) == 'y' )
    {
        grid.fillEmptyWithZeros();
        cout << "Give info on non-empty grid cells.\n";
        int row, col, value;
        while(true)
        {
            cout << "Row number (1,...,9, or type -1 if done):\n";
            cin >> row;
            if (row == -1)
            {
                break;
            }
            cout << "Column number (1,..,9):\n";
            cin >> col;
            
            cout << "Cell value (1,..,9):\n";
            cin >> value;
            
            grid[--row][--col] = value;
        }
    }
    else
    {
        // Alternatively give full grid here. 0 means empty cell.
        grid = {{0, 0, 3, 0, 1, 0, 0, 0, 6},
                {9, 0, 0, 0, 0, 0, 0, 5, 0},
                {1, 5, 0, 0, 0, 9, 0, 0, 8},
                {0, 0, 0, 5, 0, 0, 8, 1, 0},
                {0, 0, 0, 9, 0, 4, 0, 0, 0},
                {0, 8, 6, 0, 0, 2, 0, 0, 0},
                {5, 0, 0, 3, 0, 0, 0, 8, 2},
                {0, 4, 0, 0, 0, 0, 0, 0, 7},
                {6, 0, 0, 0, 7, 0, 1, 0, 0}};
    }
    cout << "\nInput:" << endl;
    cout << grid << endl;
    
    Solver solver(grid);
    
    
    if (solver.solveBacktracking() == true)
    {
        cout << "\nSolution:" << endl;
        cout << solver.getGrid() << endl;
    }
    else
    {
        cout << "No solution found." << endl;
    }
    
    cout << "The solution required " << solver.getCycles() << " backtracking cycles." << endl;
    
    return 0;
}
