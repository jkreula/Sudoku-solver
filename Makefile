CXX = clang++
CXXFLAGS = -Wall -O3 -std=c++2a

sudoku: sudokuMain.cpp sudokuSolver.cpp sudokuSolver.hpp sudokuGrid.hpp
	$(CXX) $(CXXFLAGS) sudokuMain.cpp sudokuSolver.cpp -o sudoku.out
