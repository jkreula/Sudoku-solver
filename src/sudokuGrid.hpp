//
//  sudokuGrid.hpp
//  
//
//  Created by Juha Kreula on 23/01/2020.
//

#ifndef sudokuGrid_h
#define sudokuGrid_h
#include <vector>
#include <iostream>

class Grid
{
public:
    Grid() = default;
    
    // Constructor
    explicit Grid(int nRows) :
    rows(nRows),
    cols(nRows), // square grid
    array(nRows)
    {
        for (auto & row : array)
            row.resize(cols);
    }
    
    // Destructor
    ~Grid() {}
        
    // Assignment operator for lvalue input grids
    template <size_t nRows, size_t nCols>
    Grid & operator= (int (&input)[nRows][nCols])
    {
        for (int row=0; row < getRows(); ++row)
            for (int col=0; col < getCols(); ++col)
                array[row][col] = std::move(input[row][col]);
        return *this;
    }
    
    // Assignment operator for rvalue input grids
    template <size_t nRows, size_t nCols>
    Grid & operator= (int (&&input)[nRows][nCols])
    {
        for (int row=0; row < getRows(); ++row)
            for (int col=0; col < getCols(); ++col)
                array[row][col] = std::move(input[row][col]);
        return *this;
    }
    
    // Overload [] operator for index access. This returns a constant.
    const std::vector<int> & operator[] (int row) const
    { return array[row]; }
    
    // Overload [] operator for index access. This returns a mutable object.
    std::vector<int> & operator[] (int row)
    { return array[row]; }
    
    // Fill empty grid with zeros
    void fillEmptyWithZeros()
    {
        for (auto & row: array)
            row = std::vector<int>(array.size(),0);
    }
    
    // Return number of rows
    int getRows() const { return rows; }
    
    // Return number of columns
    int getCols() const { return cols; }
    
    // Declare friend overloaded << operator
    friend std::ostream & operator<<(std::ostream & out, Grid & grid);
    
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> array; // Array (or matrix) for holding the numbers
    friend class Solver; // class for solving the Sudoku
};
 

#endif /* sudokuGrid_h */
