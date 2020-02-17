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
    explicit Solver(Grid & gridToBeSolved) :
    grid(gridToBeSolved),
    cycles(0)
    {
    }
    
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
    
    int getCycles() const { return cycles; }
    
private:
    Grid grid;
    int cycles;
    static const int EMPTY = 0;
};

#endif /* sudokuSolver_hpp */
