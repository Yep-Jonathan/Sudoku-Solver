#include "SudokuGrid.h"

SudokuGrid::SudokuGrid(std::string inFile) {
	
	// Initialize the Rows and Columns
	for (int i = 0; i < 9; ++i) {
		mRows[i] = SudokuRow(i);
		mColumns[i] = SudokuColumn(i);
		mBoxes[i] = SudokuBox(i);
	}

	// Read values from inFile and store them in the correct locations



}