CXX = clang++
CXXFLAGS = -Wall -O3 -std=c++2a
SRC = $(PWD)/src

sudoku: $(SRC)/sudokuMain.cpp $(SRC)/sudokuSolver.cpp $(SRC)/sudokuSolver.hpp $(SRC)/sudokuGrid.hpp
	$(CXX) $(CXXFLAGS) $(SRC)/sudokuMain.cpp $(SRC)/sudokuSolver.cpp -o sudoku.out
