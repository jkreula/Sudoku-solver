//
//  sudokuSolver.hpp
//  
//
//  Created by Juha Kreula on 22/01/2020.
//

#ifndef sudokuSolver_hpp
#define sudokuSolver_hpp

#include "sudokuGrid.hpp"

class Solver
{
public:
    // Constructor
    explicit Solver(Grid & gridToBeSolved) :
    grid(gridToBeSolved),
    cycles(0)
    {
    }
    
    // Destructor
    ~Solver () {}
    
    bool slotIsEmpty(int & row, int & col) const
    { return (grid[row][col] == EMPTY); }
    
    bool findEmptySlotInGrid(int & row, int & col) const;
    
    bool numberFoundInRow(int & row, int & number) const;
    
    bool numberFoundInColumn(int & col, int & number) const;
    
    bool numberFoundInRegion(int & regionBeginRow, int & regionBeginCol, int & number) const;
    
    bool legalAssignmentToSlot(int & row, int & col, int & number) const;
    
    bool solveBacktracking();
    
    Grid & getGrid()
    { return grid; }
    
    int getCycles() const { return cycles; } // Return the number of backtracking cycles
    
private:
    Grid grid; // Sudoku Grid object holding the numbers
    int cycles; // Number of backtracking cycles
    static const int EMPTY = 0; // variable to indicate an empty cell in the grid
};

#endif /* sudokuSolver_hpp */
