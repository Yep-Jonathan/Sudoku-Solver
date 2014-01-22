#ifndef SUDOKUGRID_HEADER
#define SUDOKUGRID_HEADER

#include <string>
#include <fstream>
#include "SudokuRow.h"
#include "SudokuColumn.h"
#include "SudokuBox.h"
#include "SudokuCell.h"



class SudokuGrid {
public:
	SudokuGrid(std::string inFile);
	~SudokuGrid();

	bool solve();
	void print();


private:
	bool isSolved();
	
	void setProductPossibilities();		// Iterates through the grid and eliminates product possibilities
	
	// solving algorithms
	bool setByOnePossibility();				// Scans the whole grid for any boxes where only one value can go
	bool setByOnlyOnePossibilityInSet();	// Scans the SudokuSets, and places a value if it can only be in one location in the set

	SudokuRow mRows[9];
	SudokuColumn mColumns[9];
	SudokuBox mBoxes[9];


};

#endif