//
//  sudokuSolver.cpp
//  
//
//  Created by Juha Kreula on 22/01/2020.
//

#include "sudokuSolver.hpp"
#include <vector>
#include <cmath>

bool Solver::findEmptySlotInGrid(int & row, int & col) const
{
    for (row = 0; row < grid.getRows(); ++row)
    {
        for (col = 0; col < grid.getCols(); ++col)
        {
            if(slotIsEmpty(row,col) == true)
                return true;
        }
    }
    return false;
}

bool Solver::numberFoundInRow(int & row, int & number) const
{
    for (int col = 0; col < grid.getCols(); ++col)
    {
        if (grid[row][col] == number)
            return true;
    }
    return false;
}

bool Solver::numberFoundInColumn(int & col, int & number) const
{
    for (auto & row : grid.array)
    {
        if (row[col] == number)
            return true;
    }
    return false;
}

bool Solver::numberFoundInRegion(int & regionBeginRow, int & regionBeginCol, int & number) const
{
    int regionSize = static_cast<int>(sqrt(grid.getRows()));
    for (int row = 0; row < regionSize; ++row)
    {
        for (int col = 0; col < regionSize; ++col)
        {
            if(grid[row + regionBeginRow][col + regionBeginCol] == number) return true;
        }
    }
    return false;
}

bool Solver::legalAssignmentToSlot(int & row, int & col, int & number) const
{
    int regionSize = static_cast<int>(sqrt(grid.getRows()));
    int regionBeginRow = row - (row % regionSize);
    int regionBeginCol = col - (col % regionSize);
    return slotIsEmpty(row,col) &&
    (not numberFoundInRow(row,number)) &&
    (not numberFoundInColumn(col,number)) &&
    (not numberFoundInRegion(regionBeginRow,regionBeginCol,number));
}

bool Solver::solveBacktracking()
{
    ++cycles;
    int row, col; // row and col variables will be as reference and modified by findEmptySlotInGrid, which looks for the values of row and col in which there is an empty cell
    
    if (findEmptySlotInGrid(row,col) == false) // Modifies the values of row and col
        return true; // No empty slots in grid
    
    for (int number = 1; number <= 9; ++number) // Loop through all numbers
    {
        if ( legalAssignmentToSlot(row, col, number) == true ) // Can we put a particular number to a specific slot?
        {
            grid[row][col] = number; // Try if assignment of a particular number here leads to a solution
            
            // Call solve recursively
            if (solveBacktracking() == true ) // Assignment worked.
                return true; // Solution was found
            
            grid[row][col] = EMPTY; // Assignment didn't work, put slot back to empty.
        }
    }
    return false; // No solution was found
}

