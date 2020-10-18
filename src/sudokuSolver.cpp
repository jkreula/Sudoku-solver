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
    /*
     This function finds if there is an empty slot in the Sudoku grid.
     The arguments row and col are references and will be modified to the location of the empty slot if one is found.
     */
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
    /*
     This function checks if a trial number is already found in a given row.
     */
    for (int col = 0; col < grid.getCols(); ++col)
    {
        if (grid[row][col] == number)
            return true;
    }
    return false;
}

bool Solver::numberFoundInColumn(int & col, int & number) const
{
    /*
     This function checks if a trial number is already found in a given column.
     */
    for (auto & row : grid.array)
    {
        if (row[col] == number)
            return true;
    }
    return false;
}

bool Solver::numberFoundInRegion(int & regionBeginRow, int & regionBeginCol, int & number) const
{
    /*
     This function checks whether a trial number is allowed to be put in a given region.
     */
    
    // The size of a smaller 'region' is given by the square root of the number of rows in the grid.
    // E.g., 9x9 grid consists of 9 regions of size 3x3.
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
    /*
     This function checks whether a trial number is allowed to be put in a given location according to the rules of Sudoku.
     */
    int regionSize = static_cast<int>(sqrt(grid.getRows()));
    int regionBeginRow = row - (row % regionSize);
    int regionBeginCol = col - (col % regionSize);
    return slotIsEmpty(row,col) &&
    ( not numberFoundInRow(row,number) ) &&
    ( not numberFoundInColumn(col,number) ) &&
    ( not numberFoundInRegion(regionBeginRow,regionBeginCol,number) );
}

bool Solver::solveBacktracking()
{
    /*
     This function does the heavy lifting in trying to find a solution to the Sudoku.
     Basically it tries to solve the puzzle recursively by trying to put a number to an empty slot and then see if it leads to a solution.
     If not, it backtracks its steps and tries with a different number.
     */
    // Increase the number of 'cycles' i.e. backtrack calls.
    ++cycles;
    /*
     row and col variables will be references and modified by findEmptySlotInGrid,
     which looks for the values of row and col in which there is an empty cell
     */
    int row, col;
    
    if (findEmptySlotInGrid(row,col) == false) // Modifies the values of row and col
        return true; // No empty slots in grid
    
    for (int number = 1; number <= 9; ++number) // Loop through all numbers
    {
        if ( legalAssignmentToSlot(row, col, number) == true ) // Can we put this number to the specific slot given by row and col?
        {
            grid[row][col] = number; // Try if assignment of a particular number here leads to a solution
            
            // Call solve recursively
            if ( solveBacktracking() == true ) // Assignment worked.
                return true; // Solution was found
            
            grid[row][col] = EMPTY; // Assignment didn't work, put slot back to empty.
        }
    }
    return false; // No solution was found
}

